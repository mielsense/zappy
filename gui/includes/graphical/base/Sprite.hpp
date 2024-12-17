/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef SPRITE_HPP
#define SPRITE_HPP

#pragma once

#include "Globals.hpp"
#include "graphical/components/Map.hpp"

#include <iostream>

namespace zappy
{
    enum Direction
    {
        DOWN = 0,
        UP = 1,
        LEFT = 2,
        RIGHT = 3
    };

    class Sprite
    {
        private:
            raylib::Texture texture;
            Map &map;
            int originalWidth, originalHeight;
            int width, height;
            int maxFrames;

            float frameTime = 0;
            int currentFrame = 0;
            float frameDuration = 0.1f;
            float scalingFactor;

        public:
            Sprite(const std::string& filename, int width, int height, int framesPerDirection, Map& map, float scalingFactor = 0.0f);
            ~Sprite() = default;

            // operators
            Sprite(Sprite&& other) noexcept;
            Sprite& operator=(Sprite&& other) noexcept;
            Sprite(const Sprite&) = delete;
            Sprite& operator=(const Sprite&) = delete;

            // class attributes
            vec2 position;
            Direction direction = Direction::DOWN;

            // class methods
            void update();
            void draw();
            void scale(float scale);

            // getters and setters
            int getOriginalHeight() const { return originalHeight; } // Get the original height
            int getWidth() const { return width; } // Get the current width
            int getHeight() const { return height; } // Get the current height
            float getScalingFactor() const { return scalingFactor; } // Get the scaling factor
    };
} // zappy

#endif // SPRITE_HPP
