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
GNL_DIR = gnl
LIBFT_DIR = libft

# Fichiers sources
SRC = $(SRC_DIR)/main.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Cible principale
all: $(NAME)

# Compilation des fichiers objets
%.o: %.c cub3d.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1A\033[KCompiling $<\r"

# Génération de l'exécutable
$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@$(CC) $(OBJ) $(LIBMLX) $(LIBFT) -o $(NAME)
	@printf "\033[38;5;220m\033[1A\033[KExecutable $(NAME) created\n\033[0m"

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@printf "\033[38;5;220m\033[1A\033[KCleaning objects\n\033[0m"

# Nettoyage complet
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@printf "\033[38;5;220m\033[1A\033[KRemoving $(NAME) and libraries\n\033[0m"

# Recompilation complète
re: fclean all

.PHONY: all clean fclean re
