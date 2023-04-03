/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:22:38 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/03 18:55:11 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/utils.h"
#include <stddef.h>

size_t	var_len(char *var)
{
	size_t	i;

	i = 1;
	if (var[0] != '$')
		return (0);
	while (ft_isalnum(var[i]) || var[i] == '_')
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

	i = 0;
	if (line[i] == '$')
		i++;
	ret = ft_strdup(&line[i]);
	i = 0;
	if (ret == NULL)
		return (NULL);
	while (ft_isalnum(ret[i]) || ret[i] == '_')
		i++;
	ret[i] = '\0';
	if (ft_isdigit(ret[0]))
		value = ft_strdup(&ret[1]);
	else
		value = getvalue(env, ret);
	free(ret);
	if (value == NULL)
		return (NULL);
	return (value);
}
