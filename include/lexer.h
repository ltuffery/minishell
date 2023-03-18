/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:54:11 by njegat            #+#    #+#             */
/*   Updated: 2023/03/18 12:44:48 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char			**cmdx;
	char			*infile;
	char			*outfile;
	pid_t			child;
	struct s_data	*next;
}	t_data;

void	lexer_handler(t_data **data, char *prompt, char **env);
t_data	*cut_prompt(t_data *data, char *prompt);

#endif