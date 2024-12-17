/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/components/Movable.hpp"
#include "data/Data.hpp"
#include "utils/Logger.hpp"

using namespace zappy;

// Movable class

Movable::Movable(const std::string &filename, int width, int height, int framesPerDirection, Map &map, vec2 coords)
    : Entity(map), sprite(filename, width, height, framesPerDirection, map, -4.0f), map(map), initialCoordinates(coords)
{
    position = coordinatesToPosition(initialCoordinates);
    coordinates = initialCoordinates;
    targetPosition = position;

    scale();
    updateCoordinates();
}

// Move constructor
Movable::Movable(Movable&& other) noexcept
    : Entity(std::move(other)), sprite(std::move(other.sprite)), map(other.map), initialCoordinates(other.initialCoordinates),
      targetPosition(other.targetPosition), movementQueue(std::move(other.movementQueue)), speed(other.speed),
      moving(other.moving), boundingBoxScale(other.boundingBoxScale)
{
}

// Copy assignment operator
Movable& Movable::operator=(const Movable& other)
{
    if (this != &other) {
        Entity::operator=(other);
        initialCoordinates = other.initialCoordinates;
        targetPosition = other.targetPosition;
        movementQueue = other.movementQueue;
        speed = other.speed;
        moving = other.moving;
        boundingBoxScale = other.boundingBoxScale;
    }
    return *this;
}

// Move assignment operator
Movable& Movable::operator=(Movable&& other) noexcept
{
    if (this != &other) {
        Entity::operator=(std::move(other));
        sprite = std::move(other.sprite);
        initialCoordinates = other.initialCoordinates;
        targetPosition = other.targetPosition;
        movementQueue = std::move(other.movementQueue);
        speed = other.speed;
        moving = other.moving;
        boundingBoxScale = other.boundingBoxScale;
    }
    return *this;
}

void
Movable::update(float deltaTime)
{
    if (moving) {
        float distance = speed * deltaTime;
        vec2 direction = Vector2Normalize(Vector2Subtract(targetPosition, position));
        position = Vector2Add(position, Vector2Scale(direction, distance));

        if (Vector2Distance(position, targetPosition) <= distance) {
            position = targetPosition;
            moving = false;
            updateCoordinates();

            if (!movementQueue.empty()) {
                vec2 nextStep = movementQueue.front();
                movementQueue.pop();
                updateDirection(nextStep);
                targetPosition = nextStep;
                moving = true;
            }
        }
    }

    // TODO : see if animate while not moving or not
//    if (!Vector2Equals(position, sprite.position)) {
        sprite.position = position;
        sprite.update();
//    }
    updateBoundingBox();
}

void
Movable::draw()
{
    sprite.draw();
    if (DEBUG) {
        if (DATA.examinePlayerId == id) {
            boundingBox.DrawLines(PINK, 2.0f);
        } else {
            boundingBox.DrawLines(GRAY, 2.0f);
        }
    }
}

void
Movable::walk(vec2 coords)
{
    if (coords.x < 0 || coords.x >= map.width || coords.y < 0 || coords.y >= map.height) {
        LOG(fmt::format("Invalid coordinates for walk [{0},{1}]", coords.x, coords.y), E);
        return;
    }

    vec2 tileCoords = positionToCoordinates(coordinatesToPosition(coords));
    generateMovementQueue(tileCoords);
    if (!movementQueue.empty()) {
        vec2 nextStep = movementQueue.front();
        movementQueue.pop();

        if (DEBUG) {
            updateDirection(nextStep);
        }
        targetPosition = nextStep;
        moving = true;
    }
}

void
Movable::scale()
{
    float scale = static_cast<float>(map.tileSize) / static_cast<float>(sprite.getOriginalHeight());
    sprite.scale(scale * 1.20f);

    position = coordinatesToPosition(initialCoordinates);
    targetPosition = position;

    float offsetX = (map.tileSize - sprite.getWidth()) / 2.0f;
    float offsetY = (map.tileSize - sprite.getHeight()) / 2.0f;  // Adjust for vertical centering

    // Apply the bounding box scaling factor
    float boundingBoxWidth = static_cast<float>(sprite.getWidth()) * boundingBoxScale;
    float boundingBoxHeight = static_cast<float>(sprite.getHeight()) * boundingBoxScale;

    boundingBox = raylib::Rectangle(
        position.x + offsetX + (sprite.getWidth() - boundingBoxWidth) / 2.0f,
        position.y + offsetY + (sprite.getHeight() - boundingBoxHeight) / 2.0f,
        boundingBoxWidth,
        boundingBoxHeight
    );

    updateCoordinates();
}


void
Movable::updateCoordinates()
{
    coordinates = positionToCoordinates(position);
}

void
Movable::set(vec2 coords)
{
    position = coordinatesToPosition(coords);
    targetPosition = position;
    updateCoordinates();
}

// Helper function to generate movement steps towards the destination
void
Movable::generateMovementQueue(vec2 destination)
{
    vec2 startCoords = positionToCoordinates(position);
    vec2 endCoords = destination;

    // Clear the existing queue
    std::queue<vec2> emptyQueue;
    std::swap(movementQueue, emptyQueue);

    // Generate steps for isometric movement (first vertical, then horizontal)
    while (startCoords.y != endCoords.y) {
        if (startCoords.y < endCoords.y) {
            startCoords.y += 1;
        } else if (startCoords.y > endCoords.y) {
            startCoords.y -= 1;
        }
        movementQueue.push(coordinatesToPosition(startCoords));
    }

    while (startCoords.x != endCoords.x) {
        if (startCoords.x < endCoords.x) {
            startCoords.x += 1;
        } else if (startCoords.x > endCoords.x) {
            startCoords.x -= 1;
        }
        movementQueue.push(coordinatesToPosition(startCoords));
    }
}

void
Movable::updateDirection(const vec2 &nextStep)
{
    if (nextStep.x > position.x) {
        sprite.direction = Direction::DOWN;
    } else if (nextStep.x < position.x) {
        sprite.direction = Direction::UP;
    } else if (nextStep.y > position.y) {
        sprite.direction = Direction::RIGHT;
    } else if (nextStep.y < position.y) {
        sprite.direction = Direction::LEFT;
    }
}
