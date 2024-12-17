/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/entities/Ressource.hpp"
#include "data/Data.hpp"
#include <random>

using namespace zappy;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Define the static map for ressource data
// The key is the RessourceType and the value is a pair of the filename and the number of frames per direction
std::unordered_map<RessourceType, std::pair<std::string, int> > Ressource::ressourceData = {
    { LINEMATE, { "pink.png", 1 } },  { DERAUMERE, { "green.png", 1 } }, { SIBUR, { "blue.png", 1 } },
    { MENDIANE, { "white.png", 1 } }, { PHIRAS, { "red.png", 1 } },      { THYSTAME, { "yellow.png", 1 } },
};

// Define the static vector for food filenames
std::vector<std::string> Ressource::foodFilenames
    = { "food1.png", "food2.png", "food3.png", "food4.png", "food5.png" };

void Ressource::initialize(RessourceType type)
{
    if (type == FOOD) {
        // randomly select a filename from the foodFilenames vector
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, foodFilenames.size() - 1);

        filename = fmt::format("{0}ressources/foods/{1}", ASSETS, foodFilenames[dis(gen)]);
        framesPerDirection = 1;
    } else {
        auto data = ressourceData[type];
        filename = fmt::format("{0}ressources/gems/{1}", ASSETS, data.first);
        framesPerDirection = data.second;
    }
    width = 16;
    height = 16;

    // Add random offset to the initial position within the tile
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-map.tileSize / 5.0f, map.tileSize / 5.0f);
    positionOffset = { dis(gen), dis(gen) };

    // Initialize random movement
    movementRadius = map.tileSize / 1.0f; // Increase the radius
    currentAngle = dis(gen) * 4.0f * M_PI;
    movementSpeed = 1.0f; // Increase the speed
    movementDirection = { std::cos(currentAngle), std::sin(currentAngle) };
}


Ressource::Ressource(RessourceType type, Map &map, vec2 coords)
    : Entity(map), sprite(fmt::format("{0}ressources/foods/food5.png", ASSETS), 0, 0, 0, map), type(type), map(map),
      initialCoordinates(coords)
{
    initialize(type);

    sprite = Sprite(filename, width, height, framesPerDirection, map, -5.5f);
    position = coordinatesToPosition(initialCoordinates);
    coordinates = initialCoordinates;
    scale();
    updateCoordinates();
}

Ressource::Ressource(Ressource &&other) noexcept : Entity(other.map),
                                                   sprite(std::move(other.sprite)),
                                                   map(other.map),
                                                   initialCoordinates(other.initialCoordinates)
{
    position = other.position;
    velocity = other.velocity;
    coordinates = other.coordinates;
    boundingBox = other.boundingBox;
    type = other.type;
    initialize(type); // Initialize based on RessourceType
}

Ressource &
Ressource::operator=(Ressource &&other) noexcept
{
    if (this != &other) {
        sprite = std::move(other.sprite);
        coordinates = other.coordinates;
        initialCoordinates = other.initialCoordinates;
        boundingBox = other.boundingBox;
        type = other.type;
        initialize(type); // Initialize based on RessourceType

        // Transfer ownership of resources if necessary
        position = other.position;
        velocity = other.velocity;
    }
    return *this;
}

void
Ressource::update(float deltaTime)
{

    updateMovement(deltaTime);
    sprite.position = position;
    sprite.update();
    updateBoundingBox();
}

void
Ressource::updateMovement(float deltaTime)
{
    // Increase the chance to change direction
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    if (dis(gen) < 0.3f) { // 30% chance to update direction
        currentAngle += dis(gen) * 4.0f * M_PI;
        movementDirection = { std::cos(currentAngle), std::sin(currentAngle) };
    }

    // Update the position
    position.x += movementDirection.x * movementSpeed * deltaTime;
    position.y += movementDirection.y * movementSpeed * deltaTime;

    // Ensure the position stays within the circular area
    vec2 center = coordinatesToPosition(initialCoordinates);
    vec2 offset = { position.x - center.x, position.y - center.y };
    float distance = std::sqrt(offset.x * offset.x + offset.y * offset.y);

    if (distance > movementRadius) {
        position.x = center.x + offset.x * (movementRadius / distance);
        position.y = center.y + offset.y * (movementRadius / distance);
    }
}

void
Ressource::draw()
{
    sprite.draw();
    if (DEBUG) {
        boundingBox.DrawLines(GRAY, 2.0f);
    }
}

void Ressource::scale()
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
Ressource::updateCoordinates()
{
    coordinates = positionToCoordinates(position);
}

void
Ressource::set(vec2 coords)
{
    position = coordinatesToPosition(coords);
    updateCoordinates();
}
