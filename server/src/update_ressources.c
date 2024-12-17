/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-sami.rolland
** File description:
** server.h
*/

#include "ressources.h"
#include "server.h"

tile_t total_current_ressources(server_t *server)
{
    tile_t tile = init_tile();

    for (int i = 0; i < server->bin_args->height; i++) {
        for (int j = 0; j < server->bin_args->width; j++) {
            tile.foodQtt += server->map[i][j].foodQtt;
            tile.linemateQtt += server->map[i][j].linemateQtt;
            tile.deraumereQtt += server->map[i][j].deraumereQtt;
            tile.siburQtt += server->map[i][j].siburQtt;
            tile.mendianeQtt += server->map[i][j].mendianeQtt;
            tile.phirasQtt += server->map[i][j].phirasQtt;
            tile.thystameQtt += server->map[i][j].thystameQtt;
        }
    }
    return tile;
}

tile_t ressources_to_be_placed(server_t *server, tile_t currentRessources)
{
    tile_t tile;

    tile.foodQtt = server->ressourcesMax.foodQtt - currentRessources.foodQtt;
    tile.linemateQtt =
        server->ressourcesMax.linemateQtt - currentRessources.linemateQtt;
    tile.deraumereQtt =
        server->ressourcesMax.deraumereQtt - currentRessources.deraumereQtt;
    tile.siburQtt =
        server->ressourcesMax.siburQtt - currentRessources.siburQtt;
    tile.mendianeQtt =
        server->ressourcesMax.mendianeQtt - currentRessources.mendianeQtt;
    tile.phirasQtt =
        server->ressourcesMax.phirasQtt - currentRessources.phirasQtt;
    tile.thystameQtt =
        server->ressourcesMax.thystameQtt - currentRessources.thystameQtt;
    return tile;
}

int has_20_units_passed(server_t *server)
{
    time_t current_time = time(NULL);
    double elapsed_time = difftime(current_time, server->ressource_clock);

    return elapsed_time >= (float)20 / server->bin_args->freq;
}

void update_map(server_t *server, tile_t neededRessources)
{
    update_linemate(server, neededRessources.linemateQtt);
    update_deraumere(server, neededRessources.deraumereQtt);
    update_sibur(server, neededRessources.siburQtt);
    update_mendiane(server, neededRessources.mendianeQtt);
    update_phiras(server, neededRessources.phirasQtt);
    update_thystame(server, neededRessources.thystameQtt);
    update_food(server, neededRessources.foodQtt);
}

void update_resources(server_t *server, int is_first_call)
{
    tile_t neededRessources;

    if (is_first_call || has_20_units_passed(server)) {
        neededRessources =
            ressources_to_be_placed(server, total_current_ressources(server));
        update_map(server, neededRessources);
        server->ressource_clock = time(NULL);
    }
}
