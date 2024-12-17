/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/scenes/Scoreboard.hpp"

using namespace zappy;

void
Scoreboard::handler()
{
    float deltaTime = GetFrameTime();
    static float totalTime = 0.0f;
    totalTime += deltaTime;

    update(deltaTime); // update
    draw(totalTime);   // draw
}

void
Scoreboard::update(float deltaTime)
{
    if (IsKeyPressed(KEY_S)) {
        DATA.currentScene = SceneType::WINDOW;
    }
}

void
Scoreboard::draw(float totalTime)
{
    BeginDrawing(); // Start drawing
    {
        ClearBackground(DARKGRAY); // Set background color
        DATA.background.draw();    // Draw the background

        // Initialize dimensions and colors for the table
        int headerTextSize = 40; // Larger text for headers
        int playerTextSize = 30; // Larger text for player details
        Color headerColor = GOLD;
        Color textColor = RAYWHITE;
        int rowHeight = 50;    // Increased row height for better readability
        int columnWidth = 300; // Increased column width

        // Starting position of the table
        int startX = 100;
        int startY = 100;

        // Draw the title for the scoreboard
        std::string scoreboardTitle = "Scoreboard :";
        DrawText(scoreboardTitle.c_str(), startX, startY, headerTextSize, headerColor);
        startY += rowHeight + 20; // Adjust startY for the first row below the title

        if (DATA.teams.empty()) {
            // Display message if there are no teams
            std::string noTeamsMsg = "No teams are currently available.";
            DrawText(noTeamsMsg.c_str(), startX, startY, playerTextSize, textColor);
        } else {
            // Draw headers for each team and prepare columns
            std::map<std::string, std::vector<Player> > teamPlayersMap;
            for (const auto &player : DATA.players) {
                teamPlayersMap[player.team].emplace_back(player.map, player.coordinates, player.sprite.direction, player.id, player.team);
            }

            std::vector<int> columnPositions;
            int x = startX;
            for (const auto &team : DATA.teams) {
                DrawText(team.c_str(), x, startY, headerTextSize, headerColor);
                columnPositions.push_back(x); // Save column positions for team headers
                x += columnWidth;             // Move to the next column
            }

            // Iterate over each team and list players
            for (size_t teamIndex = 0; teamIndex < DATA.teams.size(); ++teamIndex) {
                int y = startY + rowHeight; // Start below the headers
                const auto &team = DATA.teams[teamIndex];
                const auto &players = teamPlayersMap[team];

                if (players.empty()) {
                    std::string noPlayersMsg = "No players.";
                    DrawText(noPlayersMsg.c_str(), columnPositions[teamIndex], y, playerTextSize, textColor);
                } else {
                    for (const auto &player : players) {
                        // Format player info as "ID: Level"
                        std::string playerInfo = fmt::format("{}: Lvl {}", player.id, player.getLevel());
                        DrawText(playerInfo.c_str(), columnPositions[teamIndex], y, playerTextSize, textColor);
                        y += rowHeight; // Move to the next row within the same column
                    }
                }
            }
        }

        raylib::DrawText(
            "Press 'S' to toggle the scoreboard", WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT - 50, 20, RAYWHITE);
    }
    EndDrawing(); // End drawing
}
