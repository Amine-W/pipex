# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                      +:+ +:+         +:+      #
#    By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+         #
#                                                  +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 19:55:00 by amwahab           #+#    #+#              #
#    Updated: 2025/08/25 20:10:00 by amwahab          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Sources
SRC = main.c process.c access.c pipe.c
OBJ = $(SRC:.c=.o)

# Libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Target
NAME = pipex

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "libft ok"

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "pipex ok"

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re