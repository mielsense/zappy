/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef SCENE_HPP
#define SCENE_HPP

#pragma once

#include <raylib-cpp.hpp>

namespace zappy
{
    enum class SceneType
    {
        MENU,
        WINDOW,
        END,
        SCOREBOARD
    };

    class Scene
    {
        protected:
            raylib::Window &window;

        public:
            explicit Scene(raylib::Window &window) : window(window) {}
            virtual ~Scene() = default;

            virtual void handler() = 0;
            virtual void update(float deltaTime) = 0;
            virtual void draw(float totalTime) = 0;
    };
} // namespace zappy

#endif // SCENE_HPP
