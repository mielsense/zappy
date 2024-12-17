/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef EGG_HPP
#define EGG_HPP

#pragma once

#include "Globals.hpp"
#include "graphical/base/Sprite.hpp"
#include "graphical/components/Map.hpp"
#include "graphical/base/Entity.hpp"

namespace zappy
{
    class Egg : public Entity
    {
        private:
            Sprite sprite;
            Map &map;
            vec2 initialCoordinates;

            // egg movement

            float hoverTime;
            float hoverAmplitude;
            float hoverSpeed;

            void initialize();

        public:
            Egg(Map &map, vec2 coords = {0, 0}, uint64_t id = 0);
            Egg(Egg&& other) noexcept;
            virtual ~Egg() override = default;

            // operators
            Egg& operator=(Egg&& other) noexcept;
            Egg(const Egg&) = delete;
            Egg& operator=(const Egg&) = delete;

            // class methods
            void update(float deltaTime) override;
            void scale();
            void draw() override;
            void updateCoordinates();
            void set(vec2 coords);
    };
} // zappy

#endif // EGG_HPP
