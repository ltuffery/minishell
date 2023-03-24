/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:04:16 by njegat            #+#    #+#             */
/*   Updated: 2023/03/24 17:09:16 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

//Récupère le nom de variable dans une line contenant VAR ou VAR=VALUE ou VAR+=...
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

//savoir si une var est égal a celle de l'env. var_chr = VAR et var_env = VAR=value 
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

//Récupère la valeur d'une variable dans un env donné
char	*getvalue(char **env, char *var)
{
	int		i;
	int		j;
	int		k;
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
	k = 0;
	while (env[i][j])
	{
		arr[k] = env[i][j];
		k++;
		j++;
	}
	arr[k] = 0;
	return (arr);
}
