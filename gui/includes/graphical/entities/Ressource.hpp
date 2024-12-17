/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef RESSOURCE_HPP
#define RESSOURCE_HPP

#pragma once

#include "Globals.hpp"
#include "graphical/base/Sprite.hpp"
#include "graphical/components/Map.hpp"
#include "graphical/base/Entity.hpp"
#include <unordered_map>
#include <vector>
#include <random>
#include <cmath>

namespace zappy
{
    enum RessourceType
    {
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
        FOOD
    };

    static std::string
    getRessourceTypeString(RessourceType type)
    {
        switch (type) {
            case LINEMATE:
                return "linemate";
            case DERAUMERE:
                return "deraumere";
            case SIBUR:
                return "sibur";
            case MENDIANE:
                return "mendiane";
            case PHIRAS:
                return "phiras";
            case THYSTAME:
                return "thystame";
            case FOOD:
                return "food";
        }
        return "unknown";
    }

    class Ressource : public Entity
    {
        private:
            Sprite sprite;
            Map &map;
            vec2 initialCoordinates;

            // for the sprite
            static std::unordered_map<RessourceType, std::pair<std::string, int>> ressourceData;
            static std::vector<std::string> foodFilenames;

            std::string filename;
            int width;
            int height;
            int framesPerDirection;

            // sprite position offset animation
            vec2 movementDirection;
            float movementSpeed;
            float movementRadius;
            float currentAngle;

            void initialize(RessourceType type);
            void updateMovement(float deltaTime);

        public:
            RessourceType type;

        public:
            Ressource(RessourceType type, Map &map, vec2 coords = {0, 0});
            Ressource(Ressource&& other) noexcept;
            virtual ~Ressource() override = default;

            // operators
            Ressource& operator=(Ressource&& other) noexcept;
            Ressource(const Ressource&) = delete;
            Ressource& operator=(const Ressource&) = delete;

            // class methods
            void update(float deltaTime) override;
            void scale();
            void draw() override;
            void updateCoordinates();
            void set(vec2 coords);
    };
} // zappy

#endif // RESSOURCE_HPP
