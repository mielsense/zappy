/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef EVENTS_HPP
#define EVENTS_HPP

#pragma once

#include "data/Data.hpp"
#include "data/Server.hpp"

namespace zappy
{
    class Events
    {
        private:
            std::unordered_map<PacketType, std::function<void(std::string&)>> handlers;
            Server &server;
            Map &gameMap;

        public:
            Events(Map &game, Server &server) : gameMap(game), server(server)
            {
                // map events
                handlers[PacketType::MAP_SIZE] = [this](std::string &input) { mapSize(input); };
                handlers[PacketType::MAP_CONTENT] = [this](std::string &input) { map(input); };
                handlers[PacketType::TILE_CONTENT] = [this](std::string &input) { tile(input); };

                // player events
                handlers[PacketType::PLAYER_CONNECTION] = [this](std::string &input) { playerConnection(input); };
                handlers[PacketType::PLAYER_POSITION] = [this](std::string &input) { playerPosition(input); };
                handlers[PacketType::PLAYER_LEVEL] = [this](std::string &input) { playerLevel(input); };
                handlers[PacketType::PLAYER_INVENTORY] = [this](std::string &input) { playerInventory(input); };
                handlers[PacketType::PLAYER_DEATH] = [this](std::string &input) { playerDeath(input); };

                handlers[PacketType::EXPULSION] = [this](std::string &input) { expulsion(input); };
                handlers[PacketType::BROADCAST] = [this](std::string &input) { broadcast(input); };

                handlers[PacketType::INCANTATION_START] = [this](std::string &input) { incantationStart(input); };
                handlers[PacketType::INCANTATION_END] = [this](std::string &input) { incantationEnd(input); };

                handlers[PacketType::EGG_LAY] = [this](std::string &input) { eggLay(input); };
                handlers[PacketType::EGG_LAYED] = [this](std::string &input) { eggLayed(input); };
                handlers[PacketType::EGG_CONNECTION] = [this](std::string &input) { eggConnection(input); };
                handlers[PacketType::EGG_DEATH] = [this](std::string &input) { eggDeath(input); };

                handlers[PacketType::RESOURCE_DROP] = [this](std::string &input) { ressourceDrop(input); };
                handlers[PacketType::RESOURCE_COLLECT] = [this](std::string &input) { ressourceCollect(input); };

                // utils
                handlers[PacketType::TIME_UNIT_REQUEST] = [this](std::string &input) { timeUnitRequest(input); };
                handlers[PacketType::TIME_UNIT_MODIFICATION] = [this](std::string &input) { timeUnitModification(input); };

                handlers[PacketType::TEAM_NAMES] = [this](std::string &input) { teamNames(input); };
                handlers[PacketType::END_GAME] = [this](std::string &input) { endGame(input); };

                handlers[PacketType::SERVER_MESSAGE] = [this](std::string &input) { serverMessage(input); };
                handlers[PacketType::UNKNOWN_COMMAND] = [this](std::string &input) { unknownCommand(input); };
                handlers[PacketType::COMMAND_PARAMETER] = [this](std::string &input) { commandParameter(input); };
            }
            ~Events() = default;

            // class methods

            void handler();
            void handle(Packet &event);

            // helper methods
            uint64_t getId(std::istringstream &content); // get player id from string
            Player &getPlayer(uint64_t id); // get player from id

            // map events
            void mapSize(std::string &input); // handle map size content (msz)
            void map(std::string &input); // handle map content (msz)
            void tile(std::string &input); // handle tile content (bct)

            // player events
            void playerConnection(std::string &input); // handle player connection (pnw)
            void playerPosition(std::string &input); // handle player position (ppo)
            void playerLevel(std::string &input); // handle player level (plv)
            void playerInventory(std::string &input); // handle player inventory (pin)
            void playerDeath(std::string &input); // handle player death (pdi)

            void expulsion(std::string &input); // handle player expulsion (pex)
            void broadcast(std::string &input); // handle player broadcast (pbc)

            void incantationStart(std::string &input); // handle incantation start (pic)
            void incantationEnd(std::string &input); // handle incantation end (pie)

            void eggLay(std::string &input); // handle egg lay (pfk)
            void eggLayed(std::string &input); // handle egg layed (enw)
            void eggConnection(std::string &input); // handle egg connection (ebo)
            void eggDeath(std::string &input); // handle egg death (edi)

            void ressourceDrop(std::string &input); // handle ressource drop (pdr)
            void ressourceCollect(std::string &input); // handle ressource collect (pgt)

            // utils events
            void timeUnitRequest(std::string &input); // handle time unit request (sgt)
            void timeUnitModification(std::string &input); // handle time unit modification (sst)

            void teamNames(std::string &input); // handle team names (tna)
            void endGame(std::string &input); // handle end game (seg)

            void serverMessage(std::string &input); // handle server message (smg)
            void unknownCommand(std::string &input); // handle unknown command (suc)
            void commandParameter(std::string &input); // handle command parameter (sbp)

    }; // class Events
} // zappy

#endif // EVENTS_HPP
