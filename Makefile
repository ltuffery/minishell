# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njegat <njegat@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 10:20:47 by njegat            #+#    #+#              #
#    Updated: 2023/03/17 16:14:57 by njegat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

FLAGS = -Werror -Wextra -Wall -g

RLFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline

LINK_LIB = libft/

NAME_LIB = libft.a

SRC = src/minishell.c \
		src/parsing/parsing.c \
		src/parsing/check_quote.c \
		src/parsing/check_pipe.c

BSRC = 

OBJ = $(SRC:%.c=%.o)
BOBJ = $(BSRC:%.c=%.o)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@make -s -C $(LINK_LIB)
	@$(CC) $(FLAGS) $(RLFLAGS) $(OBJ) $(LINK_LIB)$(NAME_LIB) -o $(NAME)
	@echo "\033[4;32m--- executable created ---\n\033[0m"

all: $(NAME)

bonus: $(BOBJ)
	@make -s -C $(LINK_LIB)
	@$(CC) $(BOBJ) $(LINK_LIB)$(NAME_LIB) -o $(NAME)
	@echo "\033[4;32m--- executable created ---\n\033[0m"

clean:
	@rm -rf $(OBJ)
	@rm -rf $(BOBJ)
	@make -s -C $(LINK_LIB) clean

fclean: clean
	@rm -rf $(NAME)
	@make -s -C $(LINK_LIB) fclean
	@echo "\033[4;35m--- all creations have been deleted ---\n\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus
