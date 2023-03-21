/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:54:11 by njegat            #+#    #+#             */
/*   Updated: 2023/03/21 17:52:45 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

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
	struct s_file	*next;
}	t_file;

typedef struct s_data
{
	char			**cmdx;
	t_file			*file;
	pid_t			child;
	struct s_data	*next;
}	t_data;

void	lexer_handler(t_data **data, char *prompt, char **env);
t_data	*cut_prompt(t_data *data, char *prompt);
void	get_redirect(t_data *add, char *cmd);

#endif
