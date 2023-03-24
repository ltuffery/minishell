/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:20:22 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/24 18:27:29 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int	count_simple_quote(char *line)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' && (s_quote % 2) == 0)
			d_quote++;
		else if (line[i] == '\'' && (d_quote % 2) == 0)
			s_quote++;
		i++;
	}
	return (s_quote);
}

/*static char	*remove_quote(char *var)
{
	size_t	var_len;

	var_len = ft_strlen(var);
	if (var[0] == '\'' && var[var_len - 1] == '\'')
	{
		var[var_len - 1] = '\0';
		return (&var[1]);
	}
	if (var[0] == '"' && var[var_len - 1] == '"')
	{
		var[var_len - 1] = '\0';
		return (&var[0]);
	}
	return (var);
}*/

static char	*get_value(char *var, char *line)
{
	char	*value;
	char	*left_quote;
	size_t	line_len;
	int		s_quote;

	s_quote = count_simple_quote(line);
	if (s_quote % 2 == 0 && s_quote != 0)
		return (NULL);
	value = getenv(&var[1]);
	if (value == NULL)
		return (NULL);
	line_len = ft_strlen(line);
	left_quote = ft_strnstr(line, "$", line_len);
	return (value);
}

static char	*variable_value(char *line)
{
	char	*var;
	char	*value;

	var = ft_strtrim(line, "\"'");
	value = get_value(var, line);
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
