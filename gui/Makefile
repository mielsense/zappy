##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

.PHONY: all re clean fclean

BUILD_DIR := build
NAME := zappy_gui

all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" && make
	cp $(BUILD_DIR)/$(NAME) .

re: fclean all

clean:
	rm -rf $(BUILD_DIR)/*.o

fclean: clean
	rm -rf $(BUILD_DIR)
	rm -rf ./$(NAME)

test:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" && make
