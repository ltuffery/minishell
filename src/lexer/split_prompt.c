/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:44:17 by njegat            #+#    #+#             */
/*   Updated: 2023/03/29 17:11:45 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static t_cmd	*add_cmd(t_cmd *cmd, char *new_cmd, t_env *my_env)
{
	t_cmd	*tmp;
	t_cmd	*add;

	add = malloc(sizeof(t_cmd));
	add->fd_infile = -1;
	add->fd_outfile = -1;
	add->next = NULL;
	add->file = NULL;
	get_redirect(add, new_cmd);
	add->arg = NULL;
	get_cmd(add, new_cmd, my_env);
	free(new_cmd);
	if (cmd)
	{
		tmp = cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add;
	}
	else
		cmd = add;
	return (cmd);
}

static t_cmd	*split_pipe(t_cmd *cmd, int start, int end, char *prompt, t_env *my_env)
{
	char	*new_cmd;
	int		i;

	new_cmd = malloc(((end - start) + 2) * sizeof(char));
	i = 0;
	while (start + i < end)
	{
		new_cmd[i] = prompt[start + i];
		i++;
	}
	new_cmd[i] = 0;
	cmd = add_cmd(cmd, new_cmd, my_env);
	return (cmd);
}

t_cmd	*cut_prompt(t_cmd *cmd, char *prompt, t_env *my_env)
{
	int	i;
	int	start;
	int	s_quote;
	int	d_quote;

	i = 0;
	start = 0;
	s_quote = 0;
	d_quote = 0;
	while (prompt[i])
	{
		if (prompt[i] == '"' && (s_quote % 2) == 0)
			d_quote++;
		if (prompt[i] == '\'' && (d_quote % 2) == 0)
			s_quote++;
		if (prompt[i] == '|' && !(d_quote % 2) && !(s_quote % 2))
		{
			cmd = split_pipe(cmd, start, i, prompt, my_env);
			start = i + 1;
		}
		i++;
	}
	cmd = split_pipe(cmd, start, i, prompt, my_env);
	return (cmd);
}
