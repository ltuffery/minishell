/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:20:22 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/21 18:55:45 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static char	*get_value(char *var, int s_quote)
{
	char	*value;

	if (s_quote % 2)
		return (NULL);
	value = getenv(var);
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
	var = ft_strchr(line, '$');
	i = 0;
	while (var[i] != '\0')
	{
		if (var[i] == '\'' || var[i] == '"')
		{
			var[i] = '\0';
			continue ;
		}
		i++;
	}
	value = get_value(var, s_quote);
	if (value == NULL)
		return (line);
	return (value);
}

void	variable_handler(t_data *data)
{
	t_file	*tmp;

	tmp = data->file;
	while (tmp != NULL)
	{
		if (tmp->type != HERE_DOC)
			tmp->name = variable_value(tmp->name);
		printf("ooooooooooooooooooooooooooooooooooooooooooooooooooo %s\n", tmp->name);
		__builtin_dump_struct(tmp, &printf);
		printf("ooooooooooooooooooooooooooooooooooooooooooooooooooo\n");
		tmp = tmp->next;
	}
}
