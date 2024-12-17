/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef DATA_HPP
#define DATA_HPP

#include "Globals.hpp"
#include "graphical/components/Background.hpp"
#include "graphical/entities/Egg.hpp"
#include "graphical/entities/Player.hpp"
#include "graphical/entities/Ressource.hpp"
#include "utils/Error.hpp"
#include "graphical/Scene.hpp"

#include <chrono>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <fmt/core.h>
#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#pragma once

#define DATA data
#define DEBUG data.edit

namespace zappy
{
    // enums

    enum class PacketType {
        MAP_SIZE,
        TILE_CONTENT,
        MAP_CONTENT,
        TEAM_NAMES,
        PLAYER_CONNECTION,
        PLAYER_POSITION,
        PLAYER_LEVEL,
        PLAYER_INVENTORY,
        EXPULSION,
        BROADCAST,
        INCANTATION_START,
        INCANTATION_END,
        EGG_LAY,
        RESOURCE_DROP,
        RESOURCE_COLLECT,
        PLAYER_DEATH,
        EGG_LAYED,
        EGG_CONNECTION,
        EGG_DEATH,
        TIME_UNIT_REQUEST,
        TIME_UNIT_MODIFICATION,
        END_GAME,
        SERVER_MESSAGE,
        UNKNOWN_COMMAND,
        COMMAND_PARAMETER
};

    // helper functions

    inline std::string
    convert(PacketType data)
    {
        static const std::unordered_map<PacketType, std::string> dataToStringMap = {
            { PacketType::MAP_SIZE, "msz"},
            { PacketType::TILE_CONTENT, "bct"},
            { PacketType::MAP_CONTENT, "mct"},
            { PacketType::TEAM_NAMES, "tna"},
            { PacketType::PLAYER_CONNECTION, "pnw"},
            { PacketType::PLAYER_POSITION, "ppo"},
            { PacketType::PLAYER_LEVEL, "plv"},
            { PacketType::PLAYER_INVENTORY, "pin"},
            { PacketType::EXPULSION, "pex"},
            { PacketType::BROADCAST, "pbc"},
            { PacketType::INCANTATION_START, "pic"},
            { PacketType::INCANTATION_END, "pie"},
            { PacketType::EGG_LAY, "pfk"},
            { PacketType::RESOURCE_DROP, "pdr"},
            { PacketType::RESOURCE_COLLECT, "pgt"},
            { PacketType::PLAYER_DEATH, "pdi"},
            { PacketType::EGG_LAYED, "enw"},
            { PacketType::EGG_CONNECTION, "ebo"},
            { PacketType::EGG_DEATH, "edi"},
            { PacketType::TIME_UNIT_REQUEST, "sgt"},
            { PacketType::TIME_UNIT_MODIFICATION, "sst"},
            { PacketType::END_GAME, "seg"},
            { PacketType::SERVER_MESSAGE, "smg"},
            { PacketType::UNKNOWN_COMMAND, "suc"},
            { PacketType::COMMAND_PARAMETER, "sbp"}
        };

        auto it = dataToStringMap.find(data);
        if (it != dataToStringMap.end()) {
            return it->second;
        }
        ERROR("Invalid PacketType enum");
    }

    inline PacketType
    convert(const std::string &packet)
    {
        static const std::unordered_map<std::string, PacketType> stringToPacketMap = {
            {"msz", PacketType::MAP_SIZE},
            {"bct", PacketType::TILE_CONTENT},
            {"mct", PacketType::MAP_CONTENT},
            {"tna", PacketType::TEAM_NAMES},
            {"pnw", PacketType::PLAYER_CONNECTION},
            {"ppo", PacketType::PLAYER_POSITION},
            {"plv", PacketType::PLAYER_LEVEL},
            {"pin", PacketType::PLAYER_INVENTORY},
            {"pex", PacketType::EXPULSION},
            {"pbc", PacketType::BROADCAST},
            {"pic", PacketType::INCANTATION_START},
            {"pie", PacketType::INCANTATION_END},
            {"pfk", PacketType::EGG_LAY},
            {"pdr", PacketType::RESOURCE_DROP},
            {"pgt", PacketType::RESOURCE_COLLECT},
            {"pdi", PacketType::PLAYER_DEATH},
            {"enw", PacketType::EGG_LAYED},
            {"ebo", PacketType::EGG_CONNECTION},
            {"edi", PacketType::EGG_DEATH},
            {"sgt", PacketType::TIME_UNIT_REQUEST},
            {"sst", PacketType::TIME_UNIT_MODIFICATION},
            {"seg", PacketType::END_GAME},
            {"smg", PacketType::SERVER_MESSAGE},
            {"suc", PacketType::UNKNOWN_COMMAND },
            {"sbp", PacketType::COMMAND_PARAMETER }
        };

        auto it = stringToPacketMap.find(packet);
        if (it != stringToPacketMap.end()) {
            return it->second;
        }
        ERROR("Invalid PacketType string");
    }

    inline PacketType
    convert(const std::string &packet, std::string &remainingContent)
    {
        static const std::unordered_map<std::string, PacketType> stringToPacketMap = {
            {"msz", PacketType::MAP_SIZE},
            {"bct", PacketType::TILE_CONTENT},
            {"mct", PacketType::MAP_CONTENT},
            {"tna", PacketType::TEAM_NAMES},
            {"pnw", PacketType::PLAYER_CONNECTION},
            {"ppo", PacketType::PLAYER_POSITION},
            {"plv", PacketType::PLAYER_LEVEL},
            {"pin", PacketType::PLAYER_INVENTORY},
            {"pex", PacketType::EXPULSION},
            {"pbc", PacketType::BROADCAST},
            {"pic", PacketType::INCANTATION_START},
            {"pie", PacketType::INCANTATION_END},
            {"pfk", PacketType::EGG_LAY},
            {"pdr", PacketType::RESOURCE_DROP},
            {"pgt", PacketType::RESOURCE_COLLECT},
            {"pdi", PacketType::PLAYER_DEATH},
            {"enw", PacketType::EGG_LAYED},
            {"ebo", PacketType::EGG_CONNECTION},
            {"edi", PacketType::EGG_DEATH},
            {"sgt", PacketType::TIME_UNIT_REQUEST},
            {"sst", PacketType::TIME_UNIT_MODIFICATION},
            {"seg", PacketType::END_GAME},
            {"smg", PacketType::SERVER_MESSAGE},
            {"suc", PacketType::UNKNOWN_COMMAND },
            {"sbp", PacketType::COMMAND_PARAMETER }
        };

        for (const auto &pair : stringToPacketMap) {
            if (packet.find(pair.first) == 0) {
                remainingContent = packet;
                return pair.second;
            }
        }

        remainingContent = packet;
        return PacketType::UNKNOWN_COMMAND;
    }

    inline bool
    hasPacket(const std::string &packet)
    {
        static const std::unordered_map<std::string, PacketType> stringToPacketMap = {
            {"msz", PacketType::MAP_SIZE},
            {"bct", PacketType::TILE_CONTENT},
            {"mct", PacketType::MAP_CONTENT},
            {"tna", PacketType::TEAM_NAMES},
            {"pnw", PacketType::PLAYER_CONNECTION},
            {"ppo", PacketType::PLAYER_POSITION},
            {"plv", PacketType::PLAYER_LEVEL},
            {"pin", PacketType::PLAYER_INVENTORY},
            {"pex", PacketType::EXPULSION},
            {"pbc", PacketType::BROADCAST},
            {"pic", PacketType::INCANTATION_START},
            {"pie", PacketType::INCANTATION_END},
            {"pfk", PacketType::EGG_LAY},
            {"pdr", PacketType::RESOURCE_DROP},
            {"pgt", PacketType::RESOURCE_COLLECT},
            {"pdi", PacketType::PLAYER_DEATH},
            {"enw", PacketType::EGG_LAYED},
            {"ebo", PacketType::EGG_CONNECTION},
            {"edi", PacketType::EGG_DEATH},
            {"sgt", PacketType::TIME_UNIT_REQUEST},
            {"sst", PacketType::TIME_UNIT_MODIFICATION},
            {"seg", PacketType::END_GAME},
            {"smg", PacketType::SERVER_MESSAGE},
            {"suc", PacketType::UNKNOWN_COMMAND },
            {"sbp", PacketType::COMMAND_PARAMETER }
        };

        for (const auto &pair : stringToPacketMap) {
            if (packet.find(pair.first) == 0) {
                return true;
            }
        }

        return false;
    }

    // data structures

    struct Packet
    {
        PacketType type;
        std::string data;

        uint64_t id;
        std::chrono::time_point<std::chrono::system_clock> timestamp;

        // methods

        Packet(PacketType type = PacketType::UNKNOWN_COMMAND, std::string data = "")
            : type(type),
              data(data),
              id(generateRandomId()),
              timestamp(std::chrono::system_clock::now()) {};
    };

    struct TileContent
    {
        std::map<RessourceType, int> ressources;
    };

    struct vec2cmp
    {
        bool operator()(const Vector2& lhs, const Vector2& rhs) const {
            if (lhs.x < rhs.x) return true;
            if (lhs.x > rhs.x) return false;
            return lhs.y < rhs.y;
        }
    };

    struct Data
    {
        // server data
        std::vector<Packet> history; // history of server packets
        std::queue<Packet> current;

        // game data
        std::vector<std::string> teams; // teams names
        bool edit = false; // editor mode
        std::string winner = ""; // winner team

        // graphical data
        int fps = 60; // fps cap
        vec2 mapSize = {15, 15}; // map size
        uint64_t timeUnit = 20; // time unit in ms (tps)
        Background background;
        SceneType currentScene = SceneType::MENU; // current scene

        // entities data
        std::vector<Player> players;
        std::vector<Ressource> ressources;
        std::vector<Egg> eggs;

        // map data
        std::map<vec2, TileContent, vec2cmp> map;
        uint64_t examinePlayerId = 0;
    };

} // namespace zappy

extern zappy::Data data; // global data

// helper functions

inline std::vector<std::reference_wrapper<zappy::Player>>
getPlayersAt(const Vector2 &coordinates)
{
    std::vector<std::reference_wrapper<zappy::Player>> players;

    for (auto &player : DATA.players) {
        if (Vector2Equals(player.coordinates, coordinates)) {
            players.push_back(player);
        }
    }

    return players;
}

#endif // DATA_HPP
