/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:14:26 by njegat            #+#    #+#             */
/*   Updated: 2023/04/04 13:55:17 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>

extern int	g_status;

typedef enum e_boolean
{
	FALSE = 0,
	TRUE = 1,
}	t_boolean;

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
	t_boolean		ambiguous;
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

typedef struct s_data
{
	t_cmd	*cmd;
	char	**env;
}	t_data;

#endif
