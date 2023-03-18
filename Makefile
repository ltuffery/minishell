# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njegat <njegat@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 10:20:47 by njegat            #+#    #+#              #
#    Updated: 2023/03/18 13:17:02 by njegat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

FLAGS = -Werror -Wextra -Wall -g

RLFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline

LINK_LIB = libft/

NAME_LIB = libft.a

SRC = src/minishell.c \
		src/free_struct.c \
		src/parsing/parsing.c \
		src/parsing/check_quote.c \
		src/parsing/check_pipe.c \
		src/lexer/lexer.c \
		src/lexer/split_prompt.c

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

test:
	@clang tests/$(FILE).c src/builtins/$(FILE).c
	@./a.out
	@rm a.out

.PHONY: all clean fclean re bonus
