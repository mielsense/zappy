##
## EPITECH PROJECT, 2024
## zappy
## File description:
## vim on top !
##

GREEN := \033[1;32m
RED := \033[1;31m
YELLOW := \033[1;33m
BLUE := \033[1;34m
RESET := \033[0m

# Emoji markers
RUNNING = [$(YELLOW)~$(RESET)]
SUCCESS = [$(GREEN)✔$(RESET)]
FAILURE = [$(RED)✘$(RESET)]

# Directories
SERVER_DIR := server
GUI_DIR := gui
AI_DIR := ai

# Binaries
SERVER_BIN := zappy_server
GUI_BIN := zappy_gui
AI_BIN := zappy_ai

# Rules
all: $(SERVER_BIN) $(GUI_BIN) $(AI_BIN)

.SILENT:

$(SERVER_BIN):
	@echo "$(RUNNING)$(BLUE) 🚧 Starting compilation of $(SERVER_BIN)$(RESET)"
	@$(MAKE) -C $(SERVER_DIR)
	@cp $(SERVER_DIR)/$(SERVER_BIN) .
	@echo "$(SUCCESS)$(GREEN) 🚀 $(SERVER_BIN) compilation done$(RESET)"

$(GUI_BIN):
	@echo "$(RUNNING)$(BLUE) 🚧 Starting compilation of $(GUI_BIN)$(RESET)"
	@$(MAKE) -C $(GUI_DIR)
	@cp $(GUI_DIR)/$(GUI_BIN) .
	@echo "$(SUCCESS)$(GREEN) 🚀 $(GUI_BIN) compilation done$(RESET)"

$(AI_BIN):
	@echo "$(RUNNING)$(BLUE) 🚧 Starting preparation of $(AI_BIN)$(RESET)"
	@$(MAKE) -C $(AI_DIR)
	@cp $(AI_DIR)/$(AI_BIN) .
	@echo "$(SUCCESS)$(GREEN) 🚀 $(AI_BIN) preparation done$(RESET)"

.SILENT: clean
clean:
	@echo "$(RUNNING)$(RED) 🗑️ Cleaning all project files$(RESET)"
	@$(MAKE) -C $(SERVER_DIR) clean
	@$(MAKE) -C $(GUI_DIR) clean
	@$(MAKE) -C $(AI_DIR) clean
	@$(RM) $(SERVER_BIN) $(GUI_BIN) $(AI_BIN)

.SILENT: fclean
fclean: clean
	@echo "$(RUNNING)$(RED) 🗑️ Full cleaning done$(RESET)"
	@$(MAKE) -C $(SERVER_DIR) fclean
	@$(MAKE) -C $(GUI_DIR) fclean
	@$(MAKE) -C $(AI_DIR) fclean
	@$(RM) $(SERVER_BIN) $(GUI_BIN) $(AI_BIN)

.SILENT: re
re: fclean all

.PHONY: all clean fclean re
