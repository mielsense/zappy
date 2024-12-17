/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef MENU_HPP
#define MENU_HPP

#pragma once

#include "graphical/Scene.hpp"
#include "data/Data.hpp"
#include <fmt/core.h>

namespace zappy
{
    class Menu : public Scene
    {
        public:
            Menu(raylib::Window &window) : Scene(window) {}
            ~Menu() = default;

            // class methods
            void handler() override;
            void update(float deltaTime) override;
            void draw(float totalTime) override;

    }; // class Menu

} // namespace zappy

#endif // MENU_HPP
