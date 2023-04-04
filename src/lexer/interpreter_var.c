/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:22:38 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/04 14:33:41 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/utils.h"
#include <stddef.h>

size_t	var_len(char *var)
{
	size_t	i;

	i = 0;
	if (var[0] == '$')
		i++;
	if (var[i] == '?')
		return (i + 1);
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
	size_t	i;
	char	*ret;
	char	*value;

	i = line[0] == '$';
	if (line[i] == '?')
	{
		value = ft_itoa(g_status);
		return (value);
	}
	ret = ft_strdup(&line[i]);
	if (ret == NULL)
		return (NULL);
	i = var_len(ret);
	ret[i] = '\0';
	if (ft_isdigit(ret[0]))
		value = ft_strdup(&ret[1]);
	else
		value = getvalue(env, ret);
	free(ret);
	return (value);
}
