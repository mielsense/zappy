/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/scenes/End.hpp"

using namespace zappy;

void
End::handler()
{
    float deltaTime = GetFrameTime();
    static float totalTime = 0.0f;
    totalTime += deltaTime;

    update(deltaTime); // update
    draw(totalTime);   // draw
}

void
End::update(float deltaTime)
{
    (void)deltaTime;
}

void
End::draw(float totalTime)
{
    BeginDrawing(); // start drawing
    {
        ClearBackground(DARKGRAY);
        DATA.background.draw();

        const auto startText = fmt::format("The End");
        const auto enterText = fmt::format("{0} won !", DATA.winner);

        int endTextSize = 30;
        int winnerTextSize = 50;

        int startTextWidth = MeasureText(startText.c_str(), endTextSize);
        int enterTextWidth = MeasureText(enterText.c_str(), winnerTextSize);

        // Calculate position for centering
        int windowWidth = window.GetWidth();
        int windowHeight = window.GetHeight();

        int startX = (windowWidth / 2) - (startTextWidth / 2);
        int startY = (windowHeight / 2) - (endTextSize / 2);

        int enterX = (windowWidth / 2) - (enterTextWidth / 2);
        int enterY = (windowHeight / 2) + 50 - (winnerTextSize / 2);

        // Draw centered text
        DrawText(startText.c_str(), startX, startY, endTextSize, RED);
        DrawText(enterText.c_str(), enterX, enterY, winnerTextSize, RAYWHITE);
    }
    EndDrawing(); // end drawing
}
