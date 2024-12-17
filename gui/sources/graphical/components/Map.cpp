/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#include "graphical/components/Map.hpp"
#include "data/Data.hpp"
#include "graphical/components/Utils.hpp"

using namespace zappy;

Map::Map(int width, int height) : width(width), height(height)
{
    tileSize = MAP_DISPLAY_SIZE / ((width > height) ? width : height);

    int totalMapWidth = (width + height) * (tileSize / 2);
    int totalMapHeight = (width + height) * (tileSize / 4);

    offset = { ((WINDOW_WIDTH - totalMapWidth) / 2.0f) + (totalMapWidth / 2.3f), (WINDOW_HEIGHT - totalMapHeight) / 2.0f };
    create();
}

Map::Map(Map &&other) noexcept : width(other.width),
                                 height(other.height),
                                 offset(other.offset),
                                 tileSize(other.tileSize),
                                 tiles(std::move(other.tiles))
{
}

Map &
Map::operator=(Map &&other) noexcept
{
    if (this != &other) {
        width = other.width;
        height = other.height;
        offset = other.offset;
        tileSize = other.tileSize;
        tiles = std::move(other.tiles);
    }
    return *this;
}

void
Map::create()

{
    tiles.clear();
    tiles.resize(height, std::vector<std::shared_ptr<Tile> >(width));

    static std::string centerTile = fmt::format("{0}floors/center.png", ASSETS);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            tiles[y][x] = std::make_shared<Tile>(centerTile, tileToPixel(x, y));
        }
    }
}

void
Map::update()
{
    if (DATA.mapSize.x == width && DATA.mapSize.y == height) {
        return;
    }

    width = DATA.mapSize.x;
    height = DATA.mapSize.y;
    tileSize = MAP_DISPLAY_SIZE / (width + 2);

    create();

    // scale all entities
    for (auto &player : DATA.players) {
        player.scale();
    }
    for (auto &resource : DATA.ressources) {
        resource.scale();
    }
    for (auto &egg : DATA.eggs) {
        egg.scale();
    }
}

void
Map::draw()
{
    for (const auto &row : tiles) {
        for (const auto &tile : row) {
            tile->draw(tileSize);
        }
    }
}
