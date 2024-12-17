/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef TILESET_HPP
#define TILESET_HPP

#pragma once

#include "raylib-cpp.hpp"
#include <iostream>
#include <raylib.h>
#include <vector>

#include "Globals.hpp"

namespace zappy
{
    class Tileset
    {
        private:
            raylib::Texture edgeTexture;
            raylib::Texture centerTexture;

            int tileSize;

            void load(const std::string& edgeFilePath, const std::string& centerFilePath);

        public:
            Tileset(const std::string& edgeFilePath, const std::string& centerFilePath, int tileSize)
                : tileSize(tileSize)
            {
                load(edgeFilePath, centerFilePath);
            }
            ~Tileset() = default;

            // class methods

            void draw(Rectangle destRect, bool isEdge, vec2 origin = { 0, 0 }, float rotation = 0.0f, Color tint = WHITE);
            int getTileSize() const { return tileSize; }
    };
} // namespace zappy

#endif // TILESET_HPP
