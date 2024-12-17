/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/entities/Incantation.hpp"
#include "data/Data.hpp"

using namespace zappy;

Incantation::Incantation(Map &map, vec2 coords, Player *player)
    : Entity(map), sprite(fmt::format("{0}sprites/incantation.png", ASSETS), 72, 72, 16, map, 0.5f), map(map),
      initialCoordinates(coords), player(player), visible(false)
{
    position = coordinatesToPosition(initialCoordinates);
    coordinates = initialCoordinates;
    scale();
    updateCoordinates();
}

Incantation::Incantation(Incantation &&other) noexcept : Entity(other.map),
                                                         sprite(std::move(other.sprite)),
                                                         map(other.map),
                                                         initialCoordinates(other.initialCoordinates),
                                                         player(other.player),
                                                         visible(other.visible)
{
    position = other.position;
    velocity = other.velocity;
    coordinates = other.coordinates;
    boundingBox = other.boundingBox;
}

Incantation &
Incantation::operator=(Incantation &&other) noexcept
{
    if (this != &other) {
        sprite = std::move(other.sprite);
        coordinates = other.coordinates;
        initialCoordinates = other.initialCoordinates;
        boundingBox = other.boundingBox;
        player = other.player;
        visible = other.visible;

        // Transfer ownership of resources if necessary
        position = other.position;
        velocity = other.velocity;
    }
    return *this;
}

void
Incantation::update(float deltaTime)
{
    if (!visible)
        return;

    position = player->position;
    sprite.position = position;

    sprite.update();
    updateBoundingBox();
}

void
Incantation::draw()
{
    if (!visible)
        return;

    sprite.draw();
}

void
Incantation::scale()
{
    float scale = static_cast<float>(map.tileSize) / static_cast<float>(sprite.getOriginalHeight());
    sprite.scale(scale);
    position = coordinatesToPosition(initialCoordinates);

    position.x += positionOffset.x;
    position.y += positionOffset.y;

    float offsetX = (map.tileSize - sprite.getWidth()) / 2.0f;
    float offsetY = (map.tileSize - sprite.getHeight()) / 2.0f; // Adjust for vertical centering

    // Apply the bounding box scaling factor
    float boundingBoxWidth = static_cast<float>(sprite.getWidth());
    float boundingBoxHeight = static_cast<float>(sprite.getHeight());

    boundingBox = raylib::Rectangle(
        position.x + offsetX + (sprite.getWidth() - boundingBoxWidth) / 2.0f,
        position.y + offsetY + (sprite.getHeight() - boundingBoxHeight) / 2.0f, boundingBoxWidth, boundingBoxHeight);

    updateCoordinates();
}

void
Incantation::updateCoordinates()
{
    coordinates = positionToCoordinates(position);
}

void
Incantation::set(vec2 coords)
{
    position = coordinatesToPosition(coords);
    updateCoordinates();
}
