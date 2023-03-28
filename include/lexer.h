/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:54:11 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 18:36:49 by ltuffery         ###   ########.fr       */
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

# define GET_IS_QUOTE 1

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

typedef struct s_data
{
	char			**cmdx;
	t_file			*file;
	pid_t			child;
	int				fd_infile;
	int				fd_outfile;
	struct s_data	*next;
}	t_data;

void	lexer_handler(t_data **data, char *prompt, t_env *env);
t_data	*cut_prompt(t_data *data, char *prompt);
void	get_redirect(t_data *add, char *cmd);
void	files_handler(t_data *data, t_env *env);
void	get_cmd(t_data *data, char *cmd);
// utils
int		is_chevron(char c);
int		skip_set(char *str, char *set);
int		is_quote(char str, int get);

char	*var_value(char *line, t_env *env);

#endif
