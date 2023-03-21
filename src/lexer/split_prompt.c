/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:44:17 by njegat            #+#    #+#             */
/*   Updated: 2023/03/21 17:00:18 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static int	skip_redirect(char *cmd, int pos)
{
	while (cmd[pos] == '>' || cmd[pos] == '<')
		pos++;
	while (cmd[pos] == ' ')
		pos++;
	while (cmd[pos] != ' ' && cmd[pos])
		pos++;
	// while (cmd[pos] == ' ')
	// 	pos++;
	return (pos);
}

static int	is_quote(char *cmd, int pos)
{
	static int	s_quote;
	static int	d_quote;

	if (pos == -1)
		return ((s_quote + d_quote) % 2);
	if (cmd[pos] == '"' && (s_quote) == 0)
	{
		if (d_quote)
			d_quote = 0;
		else
			d_quote = 1;
		return (1);
	}
	else if (cmd[pos] == '\'' && (d_quote) == 0)
	{
		if (s_quote)
			s_quote = 0;
		else
			s_quote = 1;
		if (cmd[pos + 1] == '$')
			return (0);
		return (1);
	}
	return (0);
}

void	get_cmd(t_data *data, char *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(ft_strlen(cmd) * sizeof(char));
	while (cmd[i] == ' ')
		i++;
	while (cmd[i])
	{
		if (is_quote(cmd, i))
			i++;
		else if ((cmd[i] == '>' || cmd[i] == '<')  && !is_quote(NULL, -1))
			i = skip_redirect(cmd, i);
		else if (cmd[i] == ' ' && !is_quote(NULL, -1))
		{
			tmp[j] = 0;
			j = 0;
			while (tmp[j] == ' ')
				j++;
			if (tmp[j])
				data->cmdx = ft_strappend(tmp, data->cmdx);
			j = 0;
			while (cmd[i] == ' ')
				i++;
		}
		else
		{
			tmp[j] = cmd[i];
			j++;
			i++;
		}
	}
	tmp[j] = 0;
	if (tmp[0])
		data->cmdx = ft_strappend(tmp, data->cmdx);
	free(tmp);
}

static t_data	*add_cmd(t_data *data, char *cmd)
{
	t_data	*tmp;
	t_data	*add;

	add = malloc(sizeof(t_data));
	add->next = NULL;
	add->file = NULL;
	get_redirect(add, cmd);
	add->cmdx = NULL;
	get_cmd(add, cmd);
	//add->cmdx = ft_split(cmd, ' ');
	free(cmd);
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

static t_data	*split_pipe(t_data *data, int start, int end, char *prompt)
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
	data = add_cmd(data, cmd);
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
			data = split_pipe(data, start, i, prompt);
			start = i + 1;
		}
		i++;
	}
	data = split_pipe(data, start, i, prompt);
	return (data);
}
