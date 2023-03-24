/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:20:22 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/24 14:36:01 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static char	*get_value(char *var, char *line, int s_quote)
{
	char	*value;

	if (s_quote % 2 == 0 && s_quote != 0)
		if (line[0] == '\'' && line[ft_strlen(line) - 1] == '\'')
			return (NULL);
	value = getenv(&var[1]);
	if (value == NULL)
		return (NULL);
	return (value);
}

static char	*variable_value(char *line)
{
	int		i;
	int		s_quote;
	char	*var;
	char	*value;

	i = 0;
	s_quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			s_quote++;
		i++;
	}
	var = ft_strtrim(line, "\"'");
	value = get_value(var, line, s_quote);
	free(var);
	if (value == NULL)
	{
		return (line);
	}
	return (value);
}

void	variable_handler(t_data *data)
{
	t_file	*tmp;
	char	*tmp_name;

	tmp = data->file;
	while (tmp != NULL)
	{
		if (tmp->type != HERE_DOC)
		{
			tmp_name = variable_value(tmp->name);
			tmp->name = tmp_name;
		}
		else
		{
			tmp_name = tmp->name;
			tmp->name = ft_strtrim(tmp->name, "\"'");
			free(tmp_name);
		}
		printf("ooooooooooooooooooooooooooooooooooooooooooooooooooo %s\n", tmp->name);
		__builtin_dump_struct(tmp, &printf);
		printf("ooooooooooooooooooooooooooooooooooooooooooooooooooo\n");
		tmp = tmp->next;
	}
}
