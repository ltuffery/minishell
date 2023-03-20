/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:52:30 by njegat            #+#    #+#             */
/*   Updated: 2023/03/20 16:55:11 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static void	add_file(t_data *add, t_file *file)
{
	t_file	*tmp;

	tmp = add->file;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = file;
	}
	else
		add->file = file;
}

static void	get_type(t_file *file, char *cmd, int *start)
{
	if (cmd[*start] == '>')
		file->type = OUTFILE;
	else if (cmd[*start] == '<')
		file->type = INFILE;
	(*start)++;
	if (cmd[*start] == '>')
	{
		file->type = APPEND;
		(*start)++;
	}
	else if (cmd[*start] == '<')
	{
		file->type = HERE_DOC;
		(*start)++;
	}
}

static void	get_file(t_data *add, char *cmd, int *start)
{
	int		i;
	char	*tmp;
	t_file	*file;

	file = malloc(sizeof(t_file));
	get_type(file, cmd, start);
	while (cmd[*start] == ' ')
		(*start)++;
	i = 0;
	while (cmd[*start + i] != ' ' && cmd[*start + i])
		i++;
	tmp = malloc((i + 1) * sizeof(char));
	i = 0;
	while (cmd[*start + i] != ' ' && cmd[*start + i])
	{
		tmp[i] = cmd[*start + i];
		i++;
	}
	tmp[i] = 0;
	file->name = tmp;
	file->next = NULL;
	add_file(add, file);
}

void	get_redirect(t_data *add, char *cmd)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' && (s_quote % 2) == 0)
			d_quote++;
		if (cmd[i] == '\'' && (d_quote % 2) == 0)
			s_quote++;
		if ((cmd[i] == '<' || cmd[i] == '>') && !(d_quote % 2) && !(s_quote % 2))
			get_file(add, cmd, &i);
		i++;
	}
}
