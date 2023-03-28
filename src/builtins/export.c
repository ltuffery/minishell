/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:23:30 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/28 18:30:44 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/builtins.h"
#include "../../include/utils.h"

char	*var_replace(char *line, char *var_env)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(line) + 1);
	if (!new)
		return (line);
	while (line[i] && line[i] != '=')
	{
		new[i] = line[i];
		i++;
	}
	if (!line[i])
	{
		new[i] = '=';
		new[i + 1] = 0;
		free(var_env);
		return (new);
	}
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	new[i] = 0;
	free(var_env);
	return (new);
}

char	*var_append(char *line, char *var_env)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	i++;
	new = malloc((ft_strlen(var_env) + ft_strlen(line + i) + 1) * sizeof(char));
	j = 0;
	while (var_env[j])
	{
		new[j] = var_env[j];
		j++;
	}
	while (line[i])
	{
		new[j] = line[i];
		i++;
		j++;
	}
	free(var_env);
	return (new);
}

void	modif_var(char *line, t_env *my_env)
{
	char	*var;
	int		i;

	var = getvar(line);
	i = 0;
	while (!var_is_equal(var, my_env->loc_env[i]))
		i++;
	if (!remove_plus(line))
		my_env->loc_env[i] = var_replace(line, my_env->loc_env[i]);
	else
		my_env->loc_env[i] = var_append(line, my_env->loc_env[i]);
	free(var);
}

void	arg_handler(char **cmd, t_env *my_env)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!parsing_var(cmd[i]))
		{
			if (!existing_var(cmd[i], my_env))
			{
				remove_plus(cmd[i]);
				my_env->loc_env = ft_strappend(cmd[i], my_env->loc_env);
			}
			else
				modif_var(cmd[i], my_env);
		}
		i++;
	}
}

void	export_builtins(char **cmd, t_env *my_env)
{
	char	**tmp;

	if (ft_count(cmd) == 1)
	{
		tmp = arr_cpy(my_env->loc_env);
		print_by_order(tmp);
	}
	else
		arg_handler(cmd, my_env);
}
