/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:44:17 by njegat            #+#    #+#             */
/*   Updated: 2023/03/20 14:19:36 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	add_file(t_data *add, t_file *file)
{
	t_data	*tmp;

	if (add->file)
	{
		tmp = add;
		while (tmp->file->next)
			tmp->file = tmp->file->next;
		tmp->file->next = file;
	}
	else
		add->file = file;
}

static void	get_infile(t_data *add, char *cmd, int *start)
{
	int		i;
	char	*tmp;
	t_file	*file;

	file = malloc(sizeof(t_file));
	(*start)++;
	if (cmd[*start] == '<')
	{
		file->type = HERE_DOC;
		(*start)++;
	}
	else
		file->type = INFILE;
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
	//add->infile = ft_strappend(tmp, add->infile);
	//free(tmp);
}

static void	get_outfile(t_data *add, char *cmd, int *start)
{
	int		i;
	char	*tmp;
	t_file	*file;

	file = malloc(sizeof(t_file));
	(*start)++;
	if (cmd[*start] == '>')
	{
		file->type = APPEND;
		(*start)++;
	}
	else
		file->type = OUTFILE;
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
	(void)add;
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
		if (cmd[i] == '<' && !(d_quote % 2) && !(s_quote % 2))
			get_infile(add, cmd, &i);
		if (cmd[i] == '>' && !(d_quote % 2) && !(s_quote % 2))
			get_outfile(add, cmd, &i);
		i++;
	}
}

// char	*cut_cmd(char *cmd)
// {
// 	int	i;
// 	int	s_quote;
// 	int	d_quote;
// 	char	*tmp;

// 	i = 0;
// 	s_quote = 0;
// 	d_quote = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '"' && (s_quote % 2) == 0)
// 			d_quote++;
// 		if (cmd[i] == '\'' && (d_quote % 2) == 0)
// 			s_quote++;
// 		if (cmd[i] == '<' && !(d_quote % 2) && !(s_quote % 2))
// 			get_infile(add, cmd, i);
// 		if (cmd[i] == '>' && !(d_quote % 2) && !(s_quote % 2))
// 			get_outfile(add, cmd, i);
// 		i++;
// 	}
// }

static t_data	*add_cmd(t_data *data, char *cmd)
{
	t_data	*tmp;
	t_data	*add;

	add = malloc(sizeof(t_data));
	add->next = NULL;
	add->file = NULL;
	get_redirect(add, cmd);
	add->cmdx = ft_split(cmd, ' ');
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
