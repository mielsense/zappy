/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef MAP_HPP
#define MAP_HPP

#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <raylib-cpp.hpp>

#include "Globals.hpp"
#include "graphical/base/Tile.hpp"

namespace zappy
{
    class Map
    {
        public:
            int width, height;
            vec2 offset;

            std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
            int tileSize; // Size of each tile when drawn on the screen

        public:
            Map(int width, int height);
            ~Map() = default;

            // operators

            Map(Map &&other) noexcept;
            Map &operator=(Map &&other) noexcept;
            Map(const Map &) = delete;
            Map &operator=(const Map &) = delete;

            // class methods

            void update();
            void draw();
            void create();

            bool
            collision(int x, int y)
            {
                return x >= 0 && x < height && y >= 0 && y < width;
            }

            vec2
            center()
            {
                int centerX = width / 2;
                int centerY = height / 2;
                return { (float)centerX, (float)centerY };
            }

            vec2
            random()
            {
                int x = GetRandomValue(0, height - 1);
                int y = GetRandomValue(0, width - 1);
                return { (float)x, (float)y };
            }

            vec2
            tileToPixel(int x, int y)
            {
                float posX = offset.x + (x - y) * (tileSize / 2.0f);
                float posY = offset.y + (x + y) * (tileSize / 4.0f);
                return { posX, posY };
            }
    };
} // namespace zappy

#endif // MAP_HPP
