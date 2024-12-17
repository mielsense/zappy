/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef END_HPP
#define END_HPP

#pragma once

#include "graphical/Scene.hpp"
#include "data/Data.hpp"
#include <fmt/core.h>

namespace zappy
{
    class End : public Scene
    {
        public:
            End(raylib::Window &window) : Scene(window) {}
            ~End() = default;

            // class methods
            void handler() override;
            void update(float deltaTime) override;
            void draw(float totalTime) override;

    }; // class End

} // namespace zappy

#endif // END_HPP
