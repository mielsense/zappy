/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef TILE_HPP
#define TILE_HPP

#pragma once

#include "Globals.hpp"
#include <raylib-cpp.hpp>

namespace zappy
{
    class Tile
    {
        public:
            raylib::Texture texture;
            vec2 position;

        public:
            Tile(const std::string &texturePath, vec2 pos) : texture(texturePath), position(pos) {}
            ~Tile() = default;

            // class methods

            void
            draw (int tileSize) const
            {
                Rectangle destRec = { position.x, position.y, (float)tileSize, (float)tileSize };
                ::DrawTexturePro(texture, { 0, 0, (float)texture.width, (float)texture.height }, destRec, { 0, 0 }, 0.0f, WHITE);
            }
    };
}

#endif // TILE_HPP
