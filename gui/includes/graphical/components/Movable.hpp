/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#pragma once

#include <queue>
#include "Globals.hpp"
#include "graphical/base/Sprite.hpp"
#include "graphical/components/Map.hpp"
#include "graphical/base/Entity.hpp"

namespace zappy
{
    class Movable : public Entity
    {
        public:
            Sprite sprite;
            Map &map;

            vec2 initialCoordinates;
            vec2 targetPosition;
            std::queue<vec2> movementQueue;

            float speed = MOVE_SPEED;
            bool moving = false;

            float boundingBoxScale = 1.0f;

        public:
            Movable(const std::string &filename, int width, int height, int framesPerDirection, Map &map, vec2 coords = {0, 0});
            Movable(Movable&& other) noexcept;

            Movable& operator=(const Movable& other);
            Movable& operator=(Movable&& other) noexcept;

            virtual ~Movable() override = default;

            // class methods
            void update(float deltaTime) override;
            void scale();
            void draw() override;
            void updateCoordinates();
            void set(vec2 coords);
            void walk(vec2 coords);

            void
            setDirection(Direction direction)
            {
                sprite.direction = direction;
            }

        protected:
            void generateMovementQueue(vec2 destination);
            virtual void updateDirection(const vec2& nextStep);
    };
} // zappy

#endif // MOVABLE_HPP
