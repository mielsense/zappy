/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/entities/Egg.hpp"
#include "data/Data.hpp"
#include <cmath>

using namespace zappy;

Egg::Egg(Map &map, vec2 coords, uint64_t id)
    : Entity(map), sprite(fmt::format("{0}ressources/other/egg.png", ASSETS), 16, 16, 1, map, -3.5), map(map),
      initialCoordinates(coords)
{
    initialize();

    if (id != 0) {
        this->id = id;
    }

    position = coordinatesToPosition(initialCoordinates);
    coordinates = initialCoordinates;
    scale();
    updateCoordinates();
}

Egg::Egg(Egg &&other) noexcept : Entity(other.map),
                                                   sprite(std::move(other.sprite)),
                                                   map(other.map),
                                                   initialCoordinates(other.initialCoordinates)
{
    position = other.position;
    velocity = other.velocity;
    coordinates = other.coordinates;
    boundingBox = other.boundingBox;
    initialize();
}

Egg &
Egg::operator=(Egg &&other) noexcept
{
    if (this != &other) {
        sprite = std::move(other.sprite);
        coordinates = other.coordinates;
        initialCoordinates = other.initialCoordinates;
        boundingBox = other.boundingBox;

        // Transfer ownership of resources if necessary
        position = other.position;
        velocity = other.velocity;
        initialize();
    }
    return *this;
}

void
Egg::initialize()
{
    hoverTime = 0.0f;
    hoverAmplitude = 5.0f;
    hoverSpeed = 2.0f;
}

void
Egg::update(float deltaTime)
{
    hoverTime += deltaTime * hoverSpeed;
    position.y = coordinatesToPosition(initialCoordinates).y + hoverAmplitude * std::sin(hoverTime);

    sprite.position = position;
    sprite.update();
    updateBoundingBox();
}

void
Egg::draw()
{
    sprite.draw();
}

void Egg::scale()
{
    float scale = static_cast<float>(map.tileSize) / static_cast<float>(sprite.getOriginalHeight());
    sprite.scale(scale);
    position = coordinatesToPosition(initialCoordinates);

    position.x += positionOffset.x;
    position.y += positionOffset.y;

    float offsetX = (map.tileSize - sprite.getWidth()) / 2.0f;
    float offsetY = (map.tileSize - sprite.getHeight()) / 2.0f;  // Adjust for vertical centering

    // Apply the bounding box scaling factor
    float boundingBoxWidth = static_cast<float>(sprite.getWidth());
    float boundingBoxHeight = static_cast<float>(sprite.getHeight());

    boundingBox = raylib::Rectangle(
        position.x + offsetX + (sprite.getWidth() - boundingBoxWidth) / 2.0f,
        position.y + offsetY + (sprite.getHeight() - boundingBoxHeight) / 2.0f,
        boundingBoxWidth,
        boundingBoxHeight
    );

    updateCoordinates();
}


void
Egg::updateCoordinates()
{
    coordinates = positionToCoordinates(position);
}

void
Egg::set(vec2 coords)
{
    position = coordinatesToPosition(coords);
    updateCoordinates();
}
