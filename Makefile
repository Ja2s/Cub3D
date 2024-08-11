# Nom du programme à générer
NAME = cub3D

# Compiler and flags
CC = gcc

# Drapeaux de compilation
CFLAGS = -Wall -Werror -Wextra

# Librairies
LIBMLX = -L./minilibx-linux/ -lmlx_Linux -lX11 -lXext -lm
LIBFT = -Llibft -lft

# Répertoires de sources
SRC_DIR = src
PARSE_DIR = src/parsing/
GNL_DIR = gnl
LIBFT_DIR = libft

# Fichiers sources
SRC = $(SRC_DIR)/main.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c $(PARSE_DIR)get_color.c $(PARSE_DIR)get_texture.c $(PARSE_DIR)utils.c 

# Fichiers headers
HEADERS = $(SRC_DIR)/cub3d.h $(PARSE_DIR)parsing.h $(GNL_DIR)get_next_line.h

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Cible principale
all: $(NAME)

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
	@rm -rf $(OBJ) > /dev/null 2>&1
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@printf "\033[38;5;220m\033[1A\033[KCleaning objects\n\033[0m"

# Nettoyage complet
fclean: clean
	@rm -f $(NAME) > /dev/null 2>&1
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@printf "\033[38;5;220m\033[1A\033[KRemoving $(NAME) and libraries\n\033[0m"

# Recompilation complète
re: fclean all

.PHONY: all clean fclean re
