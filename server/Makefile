##
## EPITECH PROJECT, 2024
## B-NWP-400-LYN-4-1-myteams-sami.rolland
## File description:
## Makefile
##

CC = gcc

CFLAGS = -Wall -g3 -I./includes/

TARGET = zappy_server

SRCS = src/main.c \
	   src/server.c \
	   src/update_food.c \
	   src/client.c \
	   src/team.c \
	   src/parse_args.c \
	   src/init_map.c \
	   src/init_teams.c \
	   src/init_client.c \
	   src/update_ressources.c \
	   src/client_context.c \
	   src/response.c \
	   src/utils/random_bit.c \
	   src/utils/separate_by_double_quotes.c \
	   src/utils/tablen.c \
	   src/utils/split.c \
	   src/utils/player_count.c \
	   src/utils/get_player_id.c \
	   src/utils/normalize.c \
	   src/ressources/deraumere.c \
	   src/ressources/linemate.c \
	   src/ressources/mendiane.c \
	   src/ressources/phiras.c \
	   src/ressources/sibur.c \
	   src/ressources/thystame.c \
	   src/ressources/food.c \
	   src/requests.c \
	   src/commands.c \
	   src/ui_commands/msz.c \
	   src/ui_commands/bct.c \
	   src/ui_commands/mct.c \
	   src/ui_commands/tna.c \
	   src/ui_commands/ppo.c \
	   src/ui_commands/pnw.c \
	   src/ui_commands/sgt.c \
	   src/ui_commands/sst.c \
	   src/ui_commands/plv.c \
	   src/ui_commands/pin.c \
	   src/ui_commands/pic.c \
	   src/ui_commands/pdr.c \
	   src/ui_commands/pgt.c \
	   src/ai_commands/forward.c \
	   src/ai_commands/broadcast.c \
	   src/ai_commands/right.c \
	   src/ai_commands/left.c \
	   src/ai_commands/look_top.c \
	   src/ai_commands/look_bottom.c \
	   src/ai_commands/look_left.c \
	   src/ai_commands/look_right.c \
	   src/ai_commands/look.c \
	   src/ai_commands/take.c \
	   src/ai_commands/fork.c \
	   src/ai_commands/set.c \
	   src/ai_commands/start_incantation.c \
	   src/ai_commands/end_incantation.c \
	   src/ai_commands/connect_nbr.c \
	   src/ai_commands/eject.c \
	   src/ai_commands/inventory.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) *~ core

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
