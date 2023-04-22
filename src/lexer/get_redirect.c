/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:52:30 by njegat            #+#    #+#             */
/*   Updated: 2023/04/22 20:59:23 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

static void	add_file(t_cmd *add, t_file *file)
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

static void	get_type(t_file *file, char *new_cmd, int *start)
{
	if (new_cmd[*start] == '>')
		file->type = OUTFILE;
	else if (new_cmd[*start] == '<')
		file->type = INFILE;
	(*start)++;
	if (new_cmd[*start] == '>')
	{
		file->type = APPEND;
		(*start)++;
	}
	else if (new_cmd[*start] == '<')
	{
		file->type = HERE_DOC;
		(*start)++;
	}
}

static void	init_file(t_file *file)
{
	file->ambiguous = FALSE;
	file->fd = -1;
	file->name = NULL;
	file->next = NULL;
	file->type = 0;
}

static void	get_file(t_cmd *add, char *new_cmd, int *ps)
{
	int		i;
	char	*tmp;
	t_file	*file;
	int		quotes;

	file = malloc(sizeof(t_file));
	init_file(file);
	get_type(file, new_cmd, ps);
	while (new_cmd[*ps] == ' ')
		(*ps)++;
	tmp = NULL;
	i = 0;
	quotes = 0;
	while (((new_cmd[*ps + i] != ' ' && !is_chevron(new_cmd[*ps + i])) || quotes)
		&& new_cmd[*ps + i])
	{
		if (new_cmd[*ps + i] == '\'' || new_cmd[*ps + i] == '"')
			quotes = !quotes;
		tmp = add_c(tmp, new_cmd[*ps + i]);
		i++;
	}
	file->name = tmp;
	add_file(add, file);
}

void	get_redirect(t_cmd *add, char *new_cmd)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (new_cmd[i])
	{
		if (new_cmd[i] == '"' && (s_quote % 2) == 0)
			d_quote++;
		if (new_cmd[i] == '\'' && (d_quote % 2) == 0)
			s_quote++;
		if (is_chevron(new_cmd[i]) && !(d_quote % 2) && !(s_quote % 2))
			get_file(add, new_cmd, &i);
		i++;
	}
}
