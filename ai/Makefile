##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

NAME        =   zappy_ai

MAIN        =   main.py

V           ?=  @

# COLOR

GREEN       =   \e[1;32m

WHITE       =   \e[0m

ORANGE      =   \e[1;33m

all:            $(NAME)

$(NAME):
	$(V)printf "$(GREEN)Creating binary.$(WHITE)\n"
	$(V)echo "#!/usr/bin/env python3" > $(NAME)
	$(V)cat $(MAIN) >> $(NAME)
	$(V)chmod +x $(NAME)

clean:
	$(V)printf "$(ORANGE)Nothing to do for clean rule.$(WHITE)\n"

fclean:         clean
	$(V)rm -f $(NAME)
	$(V)printf "$(ORANGE)Removing binary file.$(WHITE)\n"

re:             fclean all

.PHONY:         clean fclean all re