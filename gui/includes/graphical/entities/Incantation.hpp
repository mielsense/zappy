/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef INCANTATION_HPP
#define INCANTATION_HPP

#pragma once

#include "Globals.hpp"
#include "graphical/base/Sprite.hpp"
#include "graphical/components/Map.hpp"
#include "graphical/base/Entity.hpp"

#include <vector>

namespace zappy
{
    class Player; // Forward declaration

    class Incantation : public Entity
    {
        private:
            Sprite sprite;
            Map &map;
            vec2 initialCoordinates;

            // Player link
            Player* player; // Link to player
            bool visible; // Visibility flag
            int level; // Incantation level

            std::vector<std::string> history; // History of incantation (succes or fail)

        public:
            Incantation(Map &map, vec2 coords = {0, 0}, Player* player = nullptr);
            Incantation(Incantation&& other) noexcept;
            virtual ~Incantation() override = default;

            // operators
            Incantation& operator=(Incantation&& other) noexcept;
            Incantation(const Incantation&) = delete;
            Incantation& operator=(const Incantation&) = delete;

            // class methods
            void update(float deltaTime) override;
            void draw() override;
            void scale();
            void updateCoordinates();
            void set(vec2 coords);

            void
            addHistory(const std::string &success)
            {
                history.push_back(success);
            }


            // setters and getters
            void setVisible(bool visibility) { this->visible = visibility; } // Set visibility
            bool isVisible() const { return this->visible; } // Check visibility

            void setLevel(int level) { this->level = level; } // Set level
            int getLevel() const { return this->level; } // Get level
    };
} // zappy

#endif // INCANTATION_HPP

