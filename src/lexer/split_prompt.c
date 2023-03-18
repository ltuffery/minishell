/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:44:17 by njegat            #+#    #+#             */
/*   Updated: 2023/03/18 13:30:21 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static t_data	*split_cmd(t_data *data, char *cmd)
{
	t_data	*tmp;
	t_data	*add;

	add = malloc(sizeof(t_data));
	add->cmdx = ft_split(cmd, ' ');
	free(cmd);
	add->next = NULL;
	//en attandant
	add->infile = NULL;
	add->outfile = NULL;
	//fin 
	if (data)
	{
		tmp = data;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add;
	}
	else
		data = add;
	return (data);
}

static t_data	*add_cmd(t_data *data, int start, int end, char *prompt)
{
	char	*cmd;
	int		i;

	cmd = malloc(((end - start) + 2) * sizeof(char));
	i = 0;
	while (start + i < end)
	{
		cmd[i] = prompt[start + i];
		i++;
	}
	cmd[i] = 0;
	data = split_cmd(data, cmd);
	return (data);
}

t_data	*cut_prompt(t_data *data, char *prompt)
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
			data = add_cmd(data, start, i, prompt);
			start = i + 1;
		}
		i++;
	}
	data = add_cmd(data, start, i, prompt);
	return (data);
}
