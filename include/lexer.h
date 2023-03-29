/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:54:11 by njegat            #+#    #+#             */
/*   Updated: 2023/03/29 16:49:51 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "builtins.h"

# define SIMPLE_QUOTE 1
# define DOOBLE_QUOTE 2

//	INFILE = "<"
//	HERE_DOC = "<<"
//	OUTFILE = ">"
//	APPEND = ">>"
typedef enum e_type_file
{
	INFILE = 1,
	HERE_DOC = 2,
	OUTFILE = 3,
	APPEND = 4,
}	t_type_file;

typedef struct s_file
{
	t_type_file		type;
	char			*name;
	int				fd;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			**arg;
	t_file			*file;
	pid_t			child;
	int				fd_infile;
	int				fd_outfile;
	struct s_cmd	*next;
}	t_cmd;

void	lexer_handler(t_cmd **data, char *prompt, t_env *env);
t_cmd	*cut_prompt(t_cmd *data, char *prompt, t_env *my_env);
void	get_redirect(t_cmd *add, char *cmd);
void	files_handler(t_cmd *data, t_env *env);
void	get_cmd(t_cmd *data, char *cmd, t_env *my_env);
// utils
int		is_chevron(char c);
int		skip_set(char *str, char *set);
int		is_quote(char str, int get);

char	*var_value(char *line, t_env *env);

#endif
