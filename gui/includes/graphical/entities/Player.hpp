/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once

#include "Ressource.hpp"
#include "graphical/entities/Incantation.hpp"
#include "graphical/components/Inventory.hpp"
#include "graphical/components/Movable.hpp"

#include <chrono>

namespace zappy
{
    struct Broadcast {
        std::string message;
        bool active = false;
        std::chrono::time_point<std::chrono::system_clock> start;
    };

    class Player : public Movable
    {
        private:
            static const std::string filename;
            static const int width;
            static const int height;
            static const int framesPerDirection;

            Incantation incantation;

        public:
            Inventory inventory;
            Broadcast broadcast;

            std::string team = "unknown";
            int level = 1;

        public:
            Player(Map &map, vec2 coordinates = {0, 0}, Direction direction = Direction::DOWN, uint64_t id = 0, const std::string &team = "unknown");
            Player(Player&& other) noexcept;
            ~Player() override = default;

            // operators
            Player& operator=(Player&& other) noexcept;
            Player(const Player&) = delete;
            Player& operator=(const Player&) = delete;

            // class methods
            void update(float deltaTime) override;
            void draw() override;

            int getLevel() const { return level; }

            void
            startIncantation(int level = -1)
            {
                if (level == -1) {
                    incantation.setLevel(getLevel() + 1);
                } else {
                    incantation.setLevel(level);
                }

                incantation.setVisible(true);
                incantation.scale();
            }

            void
            stopIncantation(std::string &result)
            {
                incantation.addHistory(result);
                incantation.setVisible(false);
            }

            bool
            isIncantating()
            {
                return incantation.isVisible();
            }

            int
            getIncantationLevel()
            {
                return incantation.getLevel();
            }
    };
} // zappy

#endif // PLAYER_HPP
