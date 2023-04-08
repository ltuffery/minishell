# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njegat <njegat@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 10:20:47 by njegat            #+#    #+#              #
#    Updated: 2023/04/08 08:36:08 by njegat           ###   ########.fr        #
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
		src/parsing/check_pipe.c \
		src/parsing/check_redirecting.c \
		src/lexer/lexer.c \
		src/lexer/split_prompt.c \
		src/lexer/get_redirect.c \
		src/lexer/interpreter_var.c \
		src/lexer/redirect_rename.c \
		src/lexer/get_cmd.c \
		src/lexer/lexer_utils.c \
		src/utils/free_struct.c \
		src/utils/env_utils.c \
		src/utils/signals_utils.c \
		src/builtins/export.c \
		src/builtins/export/export_parsing.c \
		src/builtins/export/export_print.c \
		src/builtins/export/export_utils.c \
		src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/exit.c \
		src/builtins/pwd.c \
		src/execution/exec_handler.c \
		src/execution/exec_utils.c \
		src/execution/files_mana.c \
		src/execution/get_path.c \
		src/execution/heredoc_handler.c \
		src/execution/simple_exec/single_cmd.c \
		src/execution/simple_exec/simple_exec_utils.c \
		src/execution/pipe/pipe_handler.c \
		src/execution/pipe/select_pipe.c \
		src/execution/pipe/pipe_utils.c \
		src/execution/pipe/pipe_dup_handler.c \
		src/signals/init.c

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
	@make -s -C libft
	@clang tests/$(FILE).c src/builtins/$(FILE).c libft/libft.a -g
	@valgrind ./a.out
	@rm a.out
	@make fclean -s -C libft 

.PHONY: all clean fclean re bonus
