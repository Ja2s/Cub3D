# Nom du programme à générer
NAME = cub3D
NAME_BONUS = cub3D_bonus

# Compiler and flags
CC = gcc

# Drapeaux de compilation
CFLAGS = -Wall -Werror -Wextra

# Librairies
LIBMLX = -L./minilibx-linux/ -lmlx_Linux -lX11 -lXext -lm
LIBFT = -Llibft -lft

# Répertoires de sources
INC_DIR = src/
BIN_DIR = src/bin/
RAY_DIR = src/bin/raycast/
BONUS_DIR = src/bonus/
PARSE_DIR = src/parsing/
GNL_DIR = gnl
LIBFT_DIR = libft

# Fichiers sources
SRC = 			$(BIN_DIR)main.c $(BIN_DIR)action_key.c $(BIN_DIR)init.c $(BIN_DIR)utils.c \
				$(BIN_DIR)player_init.c $(BIN_DIR)player_hitbox.c $(BIN_DIR)player_move.c \
				$(RAY_DIR)raycasting.c $(RAY_DIR)raycasting_utils.c \
				$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
				$(PARSE_DIR)get_color.c $(PARSE_DIR)get_texture.c $(PARSE_DIR)utils.c $(PARSE_DIR)get_map.c 

SRC_BONUS = 	$(BONUS_DIR)main.c $(BONUS_DIR)action_key.c $(BONUS_DIR)init.c $(BONUS_DIR)utils.c $(BONUS_DIR)minimap.c \
				$(BONUS_DIR)player_init.c $(BONUS_DIR)player_hitbox.c $(BONUS_DIR)player_move.c $(BONUS_DIR)player_move_bonus.c \
				$(BONUS_DIR)raycast/raycasting.c $(BONUS_DIR)raycast/raycasting_utils.c \
				$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
				$(PARSE_DIR)get_color.c $(PARSE_DIR)get_texture.c $(PARSE_DIR)utils.c $(PARSE_DIR)get_map.c 

# Fichiers headers
HEADERS = $(INC_DIR)/cub3d.h $(PARSE_DIR)parsing.h $(GNL_DIR)get_next_line.h

# Fichiers objets
OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

# Cible principale
all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	@make -C $(LIBFT_DIR) > /dev/null 2>&1
	@$(CC) $(OBJ_BONUS) $(LIBMLX) $(LIBFT) -o $(NAME_BONUS) > /dev/null 2>&1
	@printf "\033[38;5;220m\033[1A\033[KExecutable $(NAME_BONUS) created\n\033[0m"

# Compilation des fichiers objets
%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 2>&1
	@printf "\033[1A\033[KCompiling $<\r"

# Génération de l'exécutable
$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR) > /dev/null 2>&1
	@$(CC) $(OBJ) $(LIBMLX) $(LIBFT) -o $(NAME) > /dev/null 2>&1
	@printf "\033[38;5;220m\033[1A\033[KExecutable $(NAME) created\n\033[0m"

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ) $(OBJ_BONUS) > /dev/null 2>&1
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@printf "\033[38;5;220m\033[1A\033[KCleaning objects\n\033[0m"

# Nettoyage complet
fclean: clean 
	@rm -f $(NAME) > /dev/null 2>&1
	@rm -f $(NAME_BONUS) > /dev/null 2>&1
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@printf "\033[38;5;220m\033[1A\033[KRemoving $(NAME), $(NAME_BONUS) and libraries\n\033[0m"

# Recompilation complète
re: fclean all

.PHONY: all clean fclean re bonus

