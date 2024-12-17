/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/base/Sprite.hpp"
#include "data/Data.hpp"

using namespace zappy;

Sprite::Sprite(
    const std::string &filename,
    int width,
    int height,
    int framesPerDirection,
    Map &map,
    float scalingFactor)
    : texture(filename), width(width), height(height), maxFrames(framesPerDirection), position({ 0, 0 }), map(map),
      originalHeight(height), originalWidth(width), scalingFactor(scalingFactor)
{
    if (scalingFactor != 0.0f)
        scale(scalingFactor);

}

Sprite::Sprite(Sprite &&other) noexcept : texture(std::move(other.texture)),
                                          width(other.width),
                                          height(other.height),
                                          maxFrames(other.maxFrames),
                                          frameTime(other.frameTime),
                                          currentFrame(other.currentFrame),
                                          frameDuration(other.frameDuration),
                                          position(other.position),
                                          direction(other.direction),
                                          map(other.map),
                                          originalHeight(other.originalHeight),
                                          originalWidth(other.originalWidth),
                                          scalingFactor(other.scalingFactor)
{
}

Sprite &
Sprite::operator=(Sprite &&other) noexcept
{
    if (this != &other) {
        texture = std::move(other.texture);
        width = other.width;
        height = other.height;
        maxFrames = other.maxFrames;
        frameTime = other.frameTime;
        currentFrame = other.currentFrame;
        frameDuration = other.frameDuration;
        position = other.position;
        direction = other.direction;
        originalHeight = other.originalHeight;
        originalWidth = other.originalWidth;
        scalingFactor = other.scalingFactor;
    }
    return *this;
}

void
Sprite::update()
{
    frameTime += GetFrameTime();
    if (frameTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % maxFrames;
        frameTime = 0;
    }
}

void
Sprite::draw()
{
    float offsetX = (map.tileSize - width) * 0.5f;
    float offsetY = (map.tileSize - height) * 0.5f;

    // Define the source rectangle from the sprite sheet
    Rectangle frameRect = {
            static_cast<float>(originalWidth * currentFrame),  // X coordinate
            static_cast<float>(originalHeight * direction),    // Y coordinate
            static_cast<float>(originalWidth),                 // Width
            static_cast<float>(originalHeight)                 // Height
    };

    // Define the destination rectangle on the screen
    Rectangle spriteRect = {
            position.x + offsetX,  // Adjusted X coordinate
            position.y + offsetY,  // Adjusted Y coordinate
            static_cast<float>(width),    // Width of the sprite
            static_cast<float>(height)    // Height of the sprite
    };

    // Draw the sprite with the specified source and destination rectangles
    texture.Draw(frameRect, spriteRect);
}

void
Sprite::scale(float scale)
{
    width = static_cast<int>(originalWidth * (scale + scalingFactor));
    height = static_cast<int>(originalHeight * (scale + scalingFactor));

    // Ensure the sprite is at least 1/3 of a tile
    if (width < map.tileSize / 3) {
        width = map.tileSize / 3;
    }

    // Ensure the sprite is at least 1/3 of a tile
    if (height < map.tileSize / 3) {
        height = map.tileSize / 3;
    }
}
