/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:26 by njegat            #+#    #+#             */
/*   Updated: 2023/04/27 05:26:34 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/utils.h"

int	existing_var(char *line, char **env)
{
	char	*var;
	int		i;

	var = getvar(line);
	if (!var)
		return (0);
	i = 0;
	while (env[i])
	{
		if (var_is_equal(var, env[i]))
		{
			free(var);
			return (1);
		}
		i++;
	}
	free(var);
	return (0);
}

int	remove_plus(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '+' && line[i] != '=')
		i++;
	if (line[i] != '+')
		return (0);
	while (line[i + 1])
	{
		line[i] = line[i + 1];
		i++;
	}
	line[i] = 0;
	return (1);
}

char	**arr_cpy(char **arr)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc((ft_count(arr) + 1) * sizeof(char *));
	if (!new)
		return (new);
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = 0;
	return (new);
}

char	**str_delete(char **str, char *delete)
{
	char	**new;
	int		i;
	int		j;

	if (!delete)
		return (NULL);
	new = malloc(ft_count(str) * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != delete)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = 0;
	free(delete);
	free(str);
	return (new);
}
