/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#pragma once

#include "Globals.hpp"
#include "graphical/components/Map.hpp"

namespace zappy
{
    class Entity
    {
        public:
            u_int64_t id;
            vec2 position;
            vec2 velocity;
            vec2 coordinates;
            raylib::Rectangle boundingBox;
            Map &map;
            vec2 positionOffset;

        public:
            Entity(Map &map) : id(generateRandomId()), position(vec2{0, 0}), velocity(vec2{0, 0}), coordinates(vec2{0, 0}), map(map) {}
            virtual ~Entity() = default;

            // operators

            // Copy constructor
            Entity(const Entity& other)
                : id(other.id),
                  position(other.position),
                  velocity(other.velocity),
                  coordinates(other.coordinates),
                  boundingBox(other.boundingBox),
                  map(other.map),
                  positionOffset(other.positionOffset) {}

            // Move constructor
            Entity(Entity&& other) noexcept
                : id(other.id),
                  position(std::move(other.position)),
                  velocity(std::move(other.velocity)),
                  coordinates(std::move(other.coordinates)),
                  boundingBox(std::move(other.boundingBox)),
                  map(other.map), // References cannot be moved, only reassigned
                  positionOffset(std::move(other.positionOffset)) {
                other.id = 0;
            }

            // Copy assignment operator
            Entity&
            operator=(const Entity& other)
            {
                if (this != &other) {
                    id = other.id;
                    position = other.position;
                    velocity = other.velocity;
                    coordinates = other.coordinates;
                    boundingBox = other.boundingBox;
                    // map reference cannot be reassigned
                    positionOffset = other.positionOffset;
                }
                return *this;
            }

            // Move assignment operator
            Entity&
            operator=(Entity&& other) noexcept
            {
                if (this != &other) {
                    id = other.id;
                    position = std::move(other.position);
                    velocity = std::move(other.velocity);
                    coordinates = std::move(other.coordinates);
                    boundingBox = std::move(other.boundingBox);
                    // map reference cannot be moved, only reassigned
                    positionOffset = std::move(other.positionOffset);
                    other.id = 0;
                }
                return *this;
            }


            // class methods
            virtual void update(float deltaTime)
            {
                position.x += velocity.x * deltaTime;
                position.y += velocity.y * deltaTime;
                updateBoundingBox();
            }

            virtual void draw() = 0;

            // Collision methods
            bool collision(const Entity &other) const { return boundingBox.CheckCollision(other.boundingBox); }
            bool collision(const raylib::Rectangle &other) const { return boundingBox.CheckCollision(other); }

            protected:
                void
                updateBoundingBox()
                {
                    // Update bounding box
                    float offsetX = (map.tileSize - boundingBox.width) / 2.0f;
                    float offsetY = (map.tileSize - boundingBox.height) / 2.0f;

                    boundingBox.x = position.x + offsetX;
                    boundingBox.y = position.y + offsetY;
                }

                vec2
                coordinatesToPosition(vec2 coords) const
                {
                    float x = map.offset.x + (coords.x - coords.y) * (map.tileSize / 2.0f);
                    float y = map.offset.y + (coords.x + coords.y) * (map.tileSize / 4.0f);
                    y -= (map.tileSize / 4.0f);  // Adjust to center the entity vertically
                    return { x, y };
                }

                vec2
                positionToCoordinates(vec2 pos) const
                {
                    float tempX = (pos.x - map.offset.x) / (map.tileSize / 2.0f);
                    float tempY = (pos.y + (map.tileSize / 4.0f) - map.offset.y) / (map.tileSize / 4.0f); // Adjust for vertical centering

                    float x = round((tempX + tempY) / 2.0f);
                    float y = round((tempY - tempX) / 2.0f);
                    return { x, y };
                }
    };
} // namespace zappy

#endif // ENTITY_HPP
