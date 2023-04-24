/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:04:16 by njegat            #+#    #+#             */
/*   Updated: 2023/04/24 16:58:43 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	cpy_env(char **env, t_data *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		data->env = ft_strappend(env[i], data->env);
		i++;
	}
}

char	*getvar(char *line)
{
	int		i;
	char	*var;

	i = 0;
	while (line[i] != '=' && line[i] != '+' && line[i])
		i++;
	var = malloc(sizeof(char) * (i + 1));
	if (var == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '=' && line[i] != '+' && line[i])
	{
		var[i] = line[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

int	var_is_equal(char *var_chr, char *var_env)
{
	int	i;

	i = 0;
	while (var_env[i] != '=' && var_env[i])
	{
		if (!var_chr)
			return (0);
		if (var_env[i] != var_chr[i])
			return (0);
		i++;
	}
	if (var_chr[i])
		return (0);
	return (1);
}

char	*getvalue(char **env, char *var)
{
	int		i;
	int		j;
	char	*arr;

	i = 0;
	if (!env || !var)
		return (NULL);
	while (env[i] && !var_is_equal(var, env[i]))
		i++;
	if (!env[i])
		return (NULL);
	j = 0;
	while (env[i][j] && env[i][j] != '=')
		j++;
	if (!env[i][j])
		return (NULL);
	j++;
	arr = malloc((ft_strlen(env[i] + j) + 1) * sizeof(char));
	ft_strlcpy(arr, &env[i][j], ft_strlen(&env[i][j]) + 1);
	return (arr);
}
