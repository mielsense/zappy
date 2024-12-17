/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#pragma once

#include "graphical/Scene.hpp"
#include "data/Data.hpp"
#include <fmt/core.h>

namespace zappy
{
    class Scoreboard : public Scene
    {
        public:
            Scoreboard(raylib::Window &window) : Scene(window) {}
            ~Scoreboard() = default;

            // class methods
            void handler() override;
            void update(float deltaTime) override;
            void draw(float totalTime) override;

    }; // class Scoreboard

} // namespace zappy

#endif // SCOREBOARD_HPP
