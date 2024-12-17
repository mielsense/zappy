/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/entities/Player.hpp"
#include "data/Data.hpp"
#include "utils/Logger.hpp"

using namespace zappy;

// Initialize static members
const std::string Player::filename = fmt::format("{0}sprites/dummy.png", ASSETS);
const int Player::width = 16;
const int Player::height = 17;
const int Player::framesPerDirection = 3;

// Player class
Player::Player(Map &map, vec2 coordinates, Direction direction, uint64_t id, const std::string &team)
    : Movable(filename, width, height, framesPerDirection, map, coordinates), incantation(map, coordinates, this)
{
    // check if coordinates are valid
    if (coordinates.x < 0 || coordinates.y < 0 || coordinates.x >= map.width || coordinates.y >= map.height) {
        LOG("Player coordinates must be positive integers. Defaulting to (0, 0)");
        coordinates = { 0, 0 };
    }

    // init values
    if (id != 0) {
        this->id = id;
    }
    this->team = team;

    setDirection(direction);
    initialCoordinates = coordinates;
    position = coordinatesToPosition(coordinates);
    targetPosition = position;

    updateBoundingBox();
}

Player::Player(Player &&other) noexcept : Movable(std::move(other)),
                                          incantation(std::move(other.incantation)),
                                          broadcast(std::move(other.broadcast)),
                                          team(std::move(other.team)),
                                          level(other.level)
{
    other.level = 1;
}

Player &
Player::operator=(Player &&other) noexcept
{
    if (this != &other) {
        Movable::operator=(std::move(other));
        incantation = std::move(other.incantation);
        broadcast = std::move(other.broadcast);
        team = std::move(other.team);
        level = other.level;

        // Reset other's members if necessary
        other.level = 1;
    }
    return *this;
}

void
Player::update(float deltaTime)
{
    // player infos
    // if there is an active broadcast display the message for 3 seconds
    if (broadcast.active) {
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - broadcast.start).count()
            >= 3) {
            broadcast.active = false;
        }
    }

    if (DATA.examinePlayerId != id || !DEBUG) {
        Movable::update(deltaTime);
        if (incantation.isVisible()) {
            incantation.update(deltaTime);
        }
        return;
    }

    // movement
    // only for debug

    vec2 newTargetPosition = targetPosition;
    Direction newDirection = sprite.direction;
    bool keyPressed = false;

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        newTargetPosition.x += map.tileSize / 2;
        newTargetPosition.y -= map.tileSize / 4;
        newDirection = Direction::RIGHT;
        keyPressed = true;
    } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        newTargetPosition.x -= map.tileSize / 2;
        newTargetPosition.y += map.tileSize / 4;
        newDirection = Direction::LEFT;
        keyPressed = true;
    } else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        newTargetPosition.x += map.tileSize / 2;
        newTargetPosition.y += map.tileSize / 4;
        newDirection = Direction::DOWN;
        keyPressed = true;
    } else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        newTargetPosition.x -= map.tileSize / 2;
        newTargetPosition.y -= map.tileSize / 4;
        newDirection = Direction::UP;
        keyPressed = true;
    }

    vec2 newCoordinates = positionToCoordinates(newTargetPosition);
    if (newCoordinates.x >= 0 && newCoordinates.x < map.width && newCoordinates.y >= 0
        && newCoordinates.y < map.height) {
        if (!moving) {
            targetPosition = newTargetPosition;
            sprite.direction = newDirection;
            moving = true;
        }
    }

    // Rest

    Movable::update(deltaTime);
    // Incantation
    if (incantation.isVisible()) {
        incantation.update(deltaTime);
    }

    //    if (!keyPressed && !moving) {
    //        sprite.direction = Direction::DOWN;
    //    }
}

void
Player::draw()
{
    // Incantation
    if (incantation.isVisible()) {
        incantation.draw();
    }

    Movable::draw();
}
