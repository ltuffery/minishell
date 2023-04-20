/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:44:17 by njegat            #+#    #+#             */
/*   Updated: 2023/04/20 18:56:52 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static t_cmd	*add_cmd(t_data *data, char *new_cmd)
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
	new_cmd = replace_variable(data, new_cmd);
	tokens_manager(add, new_cmd, data->env);
	free(new_cmd);
	if (data->cmd)
	{
		tmp = data->cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add;
	}
	else
		data->cmd = add;
	return (data->cmd);
}

static t_cmd	*split_pipe(t_data *data, int start, int end, char *prompt)
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
	data->cmd = add_cmd(data, new_cmd);
	return (data->cmd);
}

t_cmd	*cut_prompt(t_data *data, char *prompt)
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
			data->cmd = split_pipe(data, start, i, prompt);
			start = i + 1;
		}
		i++;
	}
	data->cmd = split_pipe(data, start, i, prompt);
	return (data->cmd);
}
