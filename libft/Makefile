# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 14:46:54 by rasamad           #+#    #+#              #
#    Updated: 2024/08/28 13:27:26 by rasamad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_striteri.c ft_itoa.c ft_split.c \
      ft_substr.c ft_calloc.c ft_strdup.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
      ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_atoi.c

OBJ = $(SRC:.c=.o)

BONUS = ft_lstmap_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c

BONUS_OBJ = $(BONUS:.c=.o)

NAME = libft.a

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all