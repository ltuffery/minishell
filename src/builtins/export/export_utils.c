/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:26 by njegat            #+#    #+#             */
/*   Updated: 2023/03/27 14:22:18 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"

int	existing_var(char *line, t_env *my_env)
{
	char	*value;
	char	*var;

	var = getvar(line);
	if (!var)
		return (0);
	value = getvalue(my_env->loc_env, var);
	free(var);
	if (!value)
		return (0);
	free(value);
	return (1);
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
