/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/base/Tileset.hpp"

using namespace zappy;

void
Tileset::load(const std::string &edgeFilePath, const std::string &centerFilePath)
{
    edgeTexture.Load(edgeFilePath);
    centerTexture.Load(centerFilePath);
}

void
Tileset::draw(Rectangle destRect, bool isEdge, vec2 origin, float rotation, Color tint)
{
    if (isEdge) {
        ::DrawTexturePro(edgeTexture, {0, 0, (float)tileSize, (float)tileSize}, destRect, origin, rotation, tint);
    } else {
        ::DrawTexturePro(centerTexture, {0, 0, (float)tileSize, (float)tileSize}, destRect, origin, rotation, tint);
    }
}
