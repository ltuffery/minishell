/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:22:38 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/27 08:23:05 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/utils.h"
#include <stddef.h>
#include <stdio.h>

static t_boolean	quotes(char *line, t_boolean has_dollar)
{
	if (is_quote('\0', 1) == EMPTY_QUOTE)
	{
		if (line[has_dollar] == '"' || line[has_dollar] == '\'')
			return (TRUE);
	}
	return (FALSE);
}

size_t	var_len(char *var)
{
	size_t	i;

	i = 0;
	if (var[0] == '$')
		i++;
	if (var[i] == '?')
		return (i + 1);
	if (quotes(var, i))
		return (i);
	while (var[i] != '\0' && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	return (i);
}

int	is_ambiguous(char *val)
{
	size_t	i;
	int		has_space;

	i = 0;
	has_space = 0;
	if (val == NULL)
		return (0);
	while (val[i] != '\0')
	{
		if (val[i] != ' ' && has_space)
			return (1);
		if (i >= 1)
		{
			if (val[i - 1] != ' ' && val[i] == ' ')
				has_space = 1;
		}
		i++;
	}
	return (0);
}

char	*var_value(char *line, char **env)
{
	t_boolean	has_dollar;
	size_t		len;
	char		*ret;
	char		*value;

	value = NULL;
	has_dollar = line[0] == '$';
	ret = ft_strdup(&line[0]);
	if (ret == NULL)
		return (NULL);
	len = var_len(ret);
	ret[len] = '\0';
	if (ft_isdigit(ret[has_dollar]))
		value = ft_strdup(&ret[has_dollar + 1]);
	else if (quotes(line, has_dollar))
	{
		free(ret);
		return (NULL);
	}
	else if (len == 1 && has_dollar == 1)
		value = ft_strdup("$");
	else if (line[has_dollar] == '?')
		value = ft_itoa(exitcode()->code);
	else
		value = getvalue(env, &ret[has_dollar]);
	free(ret);
	return (value);
}
