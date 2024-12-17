/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "core/Events.hpp"
#include "utils/Logger.hpp"

#include <algorithm>
#include <chrono>
#include <sstream>

using namespace zappy;

void
Events::handler()
{
    if (DATA.current.empty()) {
        return; // no event to handle
    }

    while (!DATA.current.empty()) {
        handle(DATA.current.front());
        DATA.current.pop();
    }
}

void
Events::handle(Packet &event)
{
    // check if the event is valid
    if (event.type == PacketType::UNKNOWN_COMMAND) {
        return;
    }

    // log the event (if needed)
    if (event.type != PacketType::PLAYER_POSITION && event.type != PacketType::PLAYER_LEVEL && event.type != PacketType::PLAYER_INVENTORY) {
        LOG("handling event " + convert(event.type) + " with id " + std::to_string(event.id));
    }

    // handle the event
    auto it = handlers.find(event.type);
    if (it != handlers.end()) {
        it->second(event.data);
    } else {
        LOG("No handler found for event " + convert(event.type), E);
    }
}

// helper methods

uint64_t
Events::getId(std::istringstream &content)
{
    // get the player id
    std::string id_str;
    content >> id_str;
    if (id_str.front() == '#') {
        id_str.erase(0, 1);
    } else {
        LOG(fmt::format("Possible Invalid player id : '{0}'", id_str), W);
    }

    uint64_t id = std::stoull(id_str);
    if (id == 0) {
        LOG(fmt::format("Invalid player id : '{0}'", id), W);
        return 0;
    }

    return id;
}

Player &
Events::getPlayer(uint64_t id)
{
    auto it = std::find_if(
        DATA.players.begin(), DATA.players.end(), [id](const Player &player) { return player.id == id; });

    if (it == DATA.players.end()) {
        LOG(fmt::format("Player {0} not found", id), W);
        return DATA.players.front();
    }

    return *it;
}

// map methods

void
Events::mapSize(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::MAP_SIZE)) {
        LOG("Invalid map size content : " + input, W);
        return;
    }

    // get the map size

    vec2 size;
    content >> size.x >> size.y;

    DATA.mapSize.x = size.x;
    DATA.mapSize.y = size.y;
}

void
Events::map(std::string &input)
{
    std::istringstream content(input);
    std::string line;

    // get the map content
    DATA.ressources.clear();
    while (std::getline(content, line)) {
        tile(line);
    }
}

void
Events::tile(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token; // skip the "bct" token
    if (token.empty() || token != convert(PacketType::TILE_CONTENT)) {
        LOG(fmt::format("Invalid tile content : '{0}'", input), W);
        return;
    }

    // get the tile content
    vec2 coordinates;
    content >> coordinates.x >> coordinates.y;

    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;

    content >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;

    // update the game content
    TileContent tile;

    tile.ressources[RessourceType::FOOD] = food;
    tile.ressources[RessourceType::LINEMATE] = linemate;
    tile.ressources[RessourceType::DERAUMERE] = deraumere;
    tile.ressources[RessourceType::SIBUR] = sibur;
    tile.ressources[RessourceType::MENDIANE] = mendiane;
    tile.ressources[RessourceType::PHIRAS] = phiras;
    tile.ressources[RessourceType::THYSTAME] = thystame;

    // Remove the old resources from DATA.ressources
    DATA.ressources.erase(
        std::remove_if(
            DATA.ressources.begin(), DATA.ressources.end(),
            [&coordinates](const Ressource &res) { return Vector2Equals(coordinates, res.coordinates); }),
    DATA.ressources.end());

    // Update the tile in DATA.map
    DATA.map[coordinates] = tile;

    // Add the new resources to DATA.ressources
    for (const auto &ressource : tile.ressources) {
        for (int i = 0; i < ressource.second; i++) {
            DATA.ressources.emplace_back(ressource.first, gameMap, coordinates);
        }
    }
}

// player methods

void
Events::playerConnection(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token; // skip the "pnw" token
    if (token.empty() || token != convert(PacketType::PLAYER_CONNECTION)) {
        LOG(fmt::format("Invalid player connection content : '{0}'", input), W);
        return;
    }

    // get the player content
    uint64_t id;
    vec2 coordinates;
    int orientation;
    int level;
    std::string team;

    id = getId(content);
    content >> coordinates.x >> coordinates.y >> orientation >> level >> team;

    // update the game content
    Direction direction = orientation == 1   ? Direction::UP
                          : orientation == 2 ? Direction::RIGHT
                          : orientation == 3 ? Direction::DOWN
                                             : Direction::LEFT;

    LOG(fmt::format(
        "Player {0} connected at ({1},{2}) with orientation {3} and level {4} for team {5}", id, coordinates.x,
        coordinates.y, orientation, level, team));

    server.get(PacketType::TEAM_NAMES);
    DATA.players.emplace_back(gameMap, coordinates, direction, id, team);
}

void
Events::playerPosition(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::PLAYER_POSITION)) {
        LOG("Invalid player position content : " + input, W);
        return;
    }

    // get the player position
    uint64_t id;
    vec2 position;
    int orientation;

    id = getId(content);
    content >> position.x >> position.y >> orientation;
    Direction direction = orientation == 1   ? Direction::UP
                          : orientation == 2 ? Direction::RIGHT
                          : orientation == 3 ? Direction::DOWN
                                             : Direction::LEFT;

    Player &player = getPlayer(id);

    // update the player position
    player.setDirection(direction);
    if (!Vector2Equals(player.coordinates, position)) {
        LOG("handling event " + convert(PacketType::PLAYER_POSITION));
        player.walk(position);
    }
}

void
Events::playerLevel(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::PLAYER_LEVEL)) {
        LOG("Invalid player level content : " + input, W);
        return;
    }

    // get the player position
    uint64_t id;
    int level;

    id = getId(content);
    content >> level;
    Player &player = getPlayer(id);

    // update the player position
    if (player.level != level) {
        LOG("handling event " + convert(PacketType::PLAYER_LEVEL));
        player.level = level;
    }
}

void
Events::playerInventory(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::PLAYER_INVENTORY)) {
        LOG(fmt::format("Invalid player inventory content : '{0}'", input), W);
        return;
    }

    // get the inventory content
    uint64_t id;
    vec2 size;

    id = getId(content);
    content >> size.x >> size.y;

    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;

    content >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;

    // update the game content
    std::map<RessourceType, int> count;

    count[RessourceType::FOOD] = food;
    count[RessourceType::LINEMATE] = linemate;
    count[RessourceType::DERAUMERE] = deraumere;
    count[RessourceType::SIBUR] = sibur;
    count[RessourceType::MENDIANE] = mendiane;
    count[RessourceType::PHIRAS] = phiras;
    count[RessourceType::THYSTAME] = thystame;

    Player &player = getPlayer(id);
    if (player.inventory.count != count) {
        LOG("handling event " + convert(PacketType::PLAYER_INVENTORY));
        player.inventory.count = count;

        // update the player inventory
        player.inventory.ressources.clear();
        for (auto &ressource : count) {
            for (int i = 0; i < ressource.second; i++) {
                player.inventory.ressources.emplace_back(ressource.first, gameMap, player.position);
            }
        }
    }
}

void
Events::playerDeath(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::PLAYER_DEATH)) {
        LOG("Invalid player death content : " + input, W);
        return;
    }

    // get the player id
    uint64_t id = getId(content);
    Player &player = getPlayer(id);

    // remove the player from the game
    DATA.players.erase(
        std::remove_if(
            DATA.players.begin(), DATA.players.end(), [id](const Player &player) { return player.id == id; }),
    DATA.players.end());
}

void
Events::expulsion(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::EXPULSION)) {
        LOG("Invalid expulsion content : " + input, W);
        return;
    }

    // get the player id
    uint64_t id = getId(content);
    Player &player = getPlayer(id);

    // remove the player from the game
    DATA.players.erase(
        std::remove_if(
            DATA.players.begin(), DATA.players.end(), [id](const Player &player) { return player.id == id; }),
        DATA.players.end());
}

void
Events::broadcast(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::BROADCAST)) {
        LOG("Invalid broadcast content : " + input, W);
        return;
    }

    // get the player id
    uint64_t id = getId(content);
    Player &player = getPlayer(id);

    // get the message
    std::string message;
    content >> message;

    // update the player message
    player.broadcast.message = message;
    player.broadcast.active = true;
    player.broadcast.start = std::chrono::system_clock::now();
}

void
Events::incantationStart(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::INCANTATION_START)) {
        LOG("Invalid incantation start content : " + input, W);
        return;
    }

    // get the player id
    vec2 position;
    int level;

    content >> position.x >> position.y >> level;
    uint64_t playerId = 0;
    while (true) {
        playerId = getId(content);
        if (playerId == 0) {
            break; // no more players
        }

        Player &player = getPlayer(playerId);
        player.startIncantation(level);
    }
}

void
Events::incantationEnd(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::INCANTATION_END)) {
        LOG("Invalid incantation stop content : " + input, W);
        return;
    }

    // get the player id
    vec2 position;
    std::string result;

    content >> position.x >> position.y >> result;
    auto players = getPlayersAt(position);

    // update the game content
    for (auto &player : players) {
        player.get().stopIncantation(result);
    }
}

void
Events::eggLay(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::EGG_LAY)) {
        LOG("Invalid egg lay content : " + input, W);
        return;
    }

    // get the player id
    uint64_t id = getId(content);
    Player &player = getPlayer(id);

    // TODO : add egg laying animation
}

void
Events::eggLayed(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::EGG_LAYED)) {
        LOG("Invalid egg layed content : " + input, W);
        return;
    }

    // get the egg content
    uint64_t eggId = getId(content);
    uint64_t playerId = getId(content);

    vec2 position;
    content >> position.x >> position.y;

    // update the game content
    DATA.eggs.emplace_back(gameMap, position, eggId);
}

void
Events::eggConnection(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::EGG_CONNECTION)) {
        LOG("Invalid egg connection content : " + input, W);
        return;
    }

    // get the egg content
    uint64_t eggId = getId(content);

    // update the game content
    // TODO : add egg connection animation
}

void
Events::eggDeath(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::EGG_DEATH)) {
        LOG("Invalid egg death content : " + input, W);
        return;
    }

    // get the egg content
    uint64_t eggId = getId(content);

    // remove the egg from the game
    DATA.eggs.erase(
        std::remove_if(DATA.eggs.begin(), DATA.eggs.end(), [eggId](const Egg &egg) { return egg.id == eggId; }),
        DATA.eggs.end());
}

void
Events::ressourceDrop(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::RESOURCE_DROP)) {
        LOG("Invalid ressource drop content : " + input, W);
        return;
    }

    // get the ressource content
    uint64_t PlayerId = getId(content);
    Player &player = getPlayer(PlayerId);
    uint64_t ressourceId;

    content >> ressourceId;

    // update the game content
    server.get(PacketType::TILE_CONTENT, false, fmt::format("{0} {1}", player.position.x, player.position.y));
}

void
Events::ressourceCollect(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::RESOURCE_DROP)) {
        LOG("Invalid ressource drop content : " + input, W);
        return;
    }

    // get the ressource content
    uint64_t PlayerId = getId(content);
    Player &player = getPlayer(PlayerId);
    uint64_t ressourceId;

    content >> ressourceId;

    // update the game content
    server.get(PacketType::TILE_CONTENT, false, fmt::format("{0} {1}", player.position.x, player.position.y));
}

// utils

void
Events::timeUnitRequest(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::TIME_UNIT_REQUEST)) {
        LOG("Invalid time unit request content : " + input, W);
        return;
    }

    // get the time unit
    uint64_t timeUnit;
    content >> timeUnit;
    DATA.timeUnit = timeUnit;
}

void
Events::timeUnitModification(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::TIME_UNIT_MODIFICATION)) {
        LOG("Invalid time unit modification content : " + input, W);
        return;
    }

    // get the time unit
    uint64_t timeUnit;
    content >> timeUnit;
    DATA.timeUnit = timeUnit;
}

void
Events::teamNames(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::TEAM_NAMES)) {
        LOG("Invalid team names content : " + input, W);
        return;
    }

    // get the team names
    std::string teamName;
    content >> teamName;

    // update the game content
    if (std::find(DATA.teams.begin(), DATA.teams.end(), teamName) == DATA.teams.end()) {
        DATA.teams.push_back(teamName);
    }
}

void
Events::endGame(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::END_GAME)) {
        LOG("Invalid end game content : " + input, W);
        return;
    }

    // get the winner team
    std::string teamName;
    content >> teamName;

    DATA.winner = teamName;

    // update the game content
    DATA.currentScene = SceneType::END;
}

void
Events::serverMessage(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::SERVER_MESSAGE)) {
        LOG("Invalid server message content : " + input, W);
        return;
    }

    // get the message
    std::string message;
    content >> message;

    // update the game content
    LOG("Server message : " + message);
}

void
Events::unknownCommand(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::UNKNOWN_COMMAND)) {
        LOG("Invalid unknown command content : " + input, W);
        return;
    }

    // get the command
    std::string command;
    content >> command;

    // update the game content
    LOG("Unknown command : " + command);
}

void
Events::commandParameter(std::string &input)
{
    std::istringstream content(input);
    std::string token;

    content >> token;
    if (token.empty() || token != convert(PacketType::COMMAND_PARAMETER)) {
        LOG("Invalid command parameter content : " + input, W);
        return;
    }

    // get the parameter
    std::string parameter;
    content >> parameter;

    // update the game content
    LOG("Command parameter : " + parameter);
}
