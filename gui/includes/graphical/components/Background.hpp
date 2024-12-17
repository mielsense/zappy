/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#pragma once

#include <raylib-cpp.hpp>
#include "Globals.hpp"

namespace zappy
{
    class Background
    {
        private:
            raylib::Texture texture;

        public:
            Background() = default;
            Background(const std::string &filePath) { texture.Load(filePath); }
            ~Background() = default;

            // class methods

            void
            update(const std::string &filePath)
            {
                texture.Load(filePath);
            }

            void
            draw()
            {
                Rectangle srcRect = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
                Rectangle destRect = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };
                vec2 origin = { 0.0f, 0.0f };
                float rotation = 0.0f;

                texture.Draw(srcRect, destRect, origin, rotation, WHITE);
            }

    }; // class Background
} // namespace zappy


#endif // BACKGROUND_HPP
