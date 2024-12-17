/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#pragma once

#include "graphical/entities/Ressource.hpp"

#include <iostream>
#include <fmt/core.h>
#include <map>

namespace zappy
{
    class Inventory
    {
        public:
            Inventory()
            : texture(fmt::format("{0}ressources/inventory.png", ASSETS))
            {
                count[RessourceType::FOOD] = 0;
                count[RessourceType::LINEMATE] = 0;
                count[RessourceType::DERAUMERE] = 0;
                count[RessourceType::SIBUR] = 0;
                count[RessourceType::MENDIANE] = 0;
                count[RessourceType::PHIRAS] = 0;
                count[RessourceType::THYSTAME] = 0;
            }
            ~Inventory() = default;

            // class attributes
            std::vector<Ressource> ressources;
            std::map<RessourceType, int> count;

            // graphical attributes
            raylib::Texture texture;
            vec2 position = {WINDOW_WIDTH - 90, WINDOW_HEIGHT / 2 - 200};

            // class methods

            void
            add(Ressource &ressource)
            {
                ressources.push_back(std::move(ressource));
                count[ressource.type]++;
            }

            void
            remove(Ressource &ressource)
            {
                if (ressources.empty() || count[ressource.type] == 0)
                    return;

                for (auto it = ressources.begin(); it != ressources.end(); it++) {
                    if (it->id == ressource.id) {
                        ressources.erase(it);
                        count[ressource.type]--;
                        break;
                    }
                }
            }

            void draw();

    }; // class Inventory
}

#endif // INVENTORY_HPP
