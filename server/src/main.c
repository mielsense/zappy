/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** main.c
*/

#include "parse_args.h"
#include "server.h"

void print_help_message(int error)
{
    fprintf((error) ? stderr : stdout,
        "USAGE: ./zappy_server -p port -x width -y height -c maxTeamClients "
        "-n "
        "team1 team2... -f freq\n\tport\tis the port "
        "number on which the server socket listens\n"
        "\twidth\tis the width of the world\n"
        "\theight\tis the height of the world\n"
        "\tmaxTeamClients\tis the maximum number of clients per team\n"
        "\tteam1 team2...\tis the name of the teams\n"
        "\tfreq\tis the reciprocal of time unit for execution of actions\n");
}

int main(int argc, char *argv[])
{
    int error;

    if (argc < 8) {
        error = (argc == 2 && !strcmp(argv[1], "-help")) ? 0 : 1;
        print_help_message(error ? 1 : 0);
        exit(error ? 84 : EXIT_SUCCESS);
    }
    start_server(parse_args(argc, argv));
    return EXIT_SUCCESS;
}
