/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/scenes/Menu.hpp"

using namespace zappy;

void
Menu::handler()
{
    float deltaTime = GetFrameTime();
    static float totalTime = 0.0f;
    totalTime += deltaTime;

    update(deltaTime); // update
    draw(totalTime);   // draw
}

void
Menu::update(float deltaTime)
{
    if (IsKeyPressed(KEY_ENTER)) {
        DATA.currentScene = SceneType::WINDOW;
    }
}

void
Menu::draw(float totalTime)
{
    BeginDrawing(); // start drawing
    {
        ClearBackground(DARKGRAY);
        DATA.background.draw();

        const auto startText = fmt::format("Start Zappy ?");
        const auto enterText = fmt::format("(Press Enter)");

        int startTextSize = 50;
        int enterTextSize = 20;

        int startTextWidth = MeasureText(startText.c_str(), startTextSize);
        int enterTextWidth = MeasureText(enterText.c_str(), enterTextSize);

        // Calculate position for centering
        int windowWidth = window.GetWidth();
        int windowHeight = window.GetHeight();

        int startX = (windowWidth / 2) - (startTextWidth / 2);
        int startY = (windowHeight / 2) - (startTextSize / 2);

        int enterX = (windowWidth / 2) - (enterTextWidth / 2);
        int enterY = (windowHeight / 2) + 50 - (enterTextSize / 2);

        // Draw centered text
        DrawText(startText.c_str(), startX, startY, startTextSize, RAYWHITE);
        DrawText(enterText.c_str(), enterX, enterY, enterTextSize, RAYWHITE);
    }
    EndDrawing(); // end drawing
}
