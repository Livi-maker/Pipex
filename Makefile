# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 16:57:28 by ldei-sva          #+#    #+#              #
#    Updated: 2025/02/07 23:51:23 by ldei-sva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CFLAGS = -Wall -Werror -Wextra

CC = cc

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

LIBOBJECTS = -Llibft -lft

INCLUDE = -Ilibft -I/usr/include

all: $(NAME)

$(NAME): $(OBJ) lib
	@$(CC) $(OBJ) $(LIBOBJECTS) -o $(NAME)
	@echo "compilation done"

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) 

lib:
	@make -s -C libft
	@make bonus -s -C libft

clean: 
	rm -f $(OBJ)
	make clean -s -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -s -C libft

re: fclean all
