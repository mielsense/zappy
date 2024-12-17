/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** init_map.c
*/

#include "tile.h"

tile_t calculate_required_ressources(int width, int height)
{
    tile_t tile;
    int total_tiles = width * height;

    tile.foodQtt = total_tiles * 0.5;
    tile.linemateQtt = total_tiles * 0.3;
    tile.deraumereQtt = total_tiles * 0.15;
    tile.siburQtt = total_tiles * 0.1;
    tile.mendianeQtt = total_tiles * 0.1;
    tile.phirasQtt = total_tiles * 0.08;
    tile.thystameQtt = total_tiles * 0.05;
    return tile;
}

tile_t init_tile(void)
{
    tile_t tile;

    tile.foodQtt = 0;
    tile.linemateQtt = 0;
    tile.deraumereQtt = 0;
    tile.siburQtt = 0;
    tile.mendianeQtt = 0;
    tile.phirasQtt = 0;
    tile.thystameQtt = 0;
    tile.has_player = false;
    return tile;
}

tile_t **init_map(int width, int height)
{
    tile_t **map = malloc(sizeof(tile_t *) * (height));

    for (int i = 0; i < height; i++) {
        map[i] = malloc(sizeof(tile_t) * (width));
        for (int j = 0; j < width; j++)
            map[i][j] = init_tile();
    }
    return map;
}
