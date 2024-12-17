/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/scenes/Window.hpp"
#include "graphical/base/Tileset.hpp"
#include "utils/Logger.hpp"

#include <algorithm>

using namespace zappy;

void
Window::handler()
{
    float deltaTime = GetFrameTime();
    static float totalTime = 0.0f;
    totalTime += deltaTime;

    events(); // handle events
    update(deltaTime); // update
    draw(totalTime);   // draw
}

void
Window::events()
{
    // activate editor
    if (IsKeyPressed(KEY_E)) {
        editor.active = !editor.active;
    }
    DEBUG = editor.active;
}

void
Window::updateCamera()
{
    // handle camera zoom
    zoomLevel += GetMouseWheelMove() * 0.1f;
    if (zoomLevel < 0.1f) zoomLevel = 0.1f;  // Prevent zooming out too much
    if (zoomLevel > 3.0f) zoomLevel = 3.0f;  // Prevent zooming in too much
    camera.zoom = zoomLevel;

    // handle camera panning
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if (!isPanning) {
            isPanning = true;
            prevMousePosition = GetMousePosition();
        } else {
            Vector2 currentMousePosition = GetMousePosition();
            Vector2 delta = Vector2Subtract(prevMousePosition, currentMousePosition);
            camera.target = Vector2Add(camera.target, Vector2Scale(delta, 1.0f / zoomLevel));
            prevMousePosition = currentMousePosition;
        }
    } else {
        isPanning = false;
    }
}

void
Window::update(float deltaTime)
{
    // handle scene change
    if (IsKeyPressed(KEY_S)) {
        DATA.currentScene = SceneType::SCOREBOARD;
    }

    // graphical update
    map.update();

    if (!DEBUG) updateCamera();

    // Convert mouse position to world coordinates
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

    // Check for player selection
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        bool selected = false;
        for (const auto &player : DATA.players) {
            if (CheckCollisionPointRec(mouseWorldPos, player.boundingBox)) {
                DATA.examinePlayerId = player.id;
                selected = true;
                break;
            }
        }

        if (!DEBUG && !selected) {
            DATA.examinePlayerId = 0;
        }
    }

    // update entities
    for (auto &player : DATA.players) {
        player.update(deltaTime);

        // Check for collisions with resources
//        DATA.ressources.erase(
//            std::remove_if(
//                DATA.ressources.begin(), DATA.ressources.end(),
//                [&player](auto &ressource) {
//                    if (player.collision(ressource)) {
//                        LOG(fmt::format(
//                            "Player {0} collided with resource {1} at [{2},{3}]", player.id, ressource.id,
//                            ressource.coordinates.x, ressource.coordinates.y));
//                        player.inventory.add(ressource);
//                        return true;
//                    }
//                    return false;
//                }),
//        DATA.ressources.end());
    }
    for (auto &resource : DATA.ressources) {
        resource.update(deltaTime);
    }
    for (auto &egg : DATA.eggs) {
        egg.update(deltaTime);
    }
}

void
Window::draw(float totalTime)
{
    BeginTextureMode(target); // Enable drawing to texture
    {
        DATA.background.draw();
        BeginMode2D(camera);
        {
            map.draw();

            // entities
            // player last to be on top
            for (auto &resource : DATA.ressources) {
                resource.draw();
            }
            for (auto &egg : DATA.eggs) {
                    egg.draw();
            }
            for (auto &player : DATA.players) {
                player.draw();
            }

            // draw player info (shader applied)
            if (DATA.examinePlayerId != 0 && !DEBUG) {
                auto it = std::find_if(DATA.players.begin(), DATA.players.end(), [&](const auto& player) { return player.id == DATA.examinePlayerId; });
                if (it != DATA.players.end()) {

                    // only if the player is not incantating
                    // as there is already a text for incantation level
                    if (it->isIncantating()) {
                        DrawText(fmt::format("{0} -> {1}", it->level, it->getIncantationLevel()).c_str(), it->position.x + 35, it->position.y - 40, 20, GOLD);
                    } else if (it->broadcast.active) {
                        DrawText("Broadcasting ...", it->position.x + 20, it->position.y - 40, 20, RAYWHITE);
                        DrawText(it->broadcast.message.c_str(), it->position.x + 20, it->position.y - 20, 20, GOLD);
                    } else {
                        DrawText(fmt::format("Player {0}", it->id).c_str(), it->position.x + 20, it->position.y - 60, 20, RAYWHITE);
                        DrawText(fmt::format("Team {0}", it->team).c_str(), it->position.x + 20, it->position.y - 40, 20, RAYWHITE);
                        DrawText(fmt::format("Level {0}", it->level).c_str(), it->position.x + 20, it->position.y - 20, 20, RAYWHITE);
                    }
                }
            }
        }
        EndMode2D();

        // draw inventory
        if (DATA.examinePlayerId != 0 && !DEBUG) {
            auto it = std::find_if(DATA.players.begin(), DATA.players.end(),
                                   [&](const auto& player) { return player.id == DATA.examinePlayerId; });
            if (it != DATA.players.end()) {
                it->inventory.draw();
            }
        }

        // text info
        raylib::DrawText(fmt::format("{0} fps", GetFPS()), WINDOW_WIDTH - 75, 10, 20, BLACK);
        raylib::DrawText("'Left click' on a player to select", WINDOW_WIDTH / 2 - 175, WINDOW_HEIGHT - 75, 20, BLACK);
        raylib::DrawText("Press 'S' to toggle the scoreboard", WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT - 50, 20, BLACK);
    }
    EndTextureMode(); // End drawing to texture

    BeginDrawing(); // start raylib
    {
        window.ClearBackground(DARKGRAY);
        BeginShaderMode(shader); // start shader
        {
            int resolutionLoc = GetShaderLocation(shader, "resolution");
            float resolution[2] = { (float)target.texture.width, (float)target.texture.height };
            SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

            int timeLoc = GetShaderLocation(shader, "time");
            SetShaderValue(shader, timeLoc, &totalTime, SHADER_UNIFORM_FLOAT);

            DrawTextureRec(
                target.texture,
                (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height },
                (Vector2){ 0, 0 },
                WHITE
            );
        }
        EndShaderMode(); // end shader
        overlay();
    }
    EndDrawing(); // end raylib
}

// code in overlay will not be affected by shader
void
Window::overlay()
{
    rlImGuiBegin(); // start imgui
    {
        if (editor.active) {
            editor.update();
        }
    }
    rlImGuiEnd(); // end imgui
}
