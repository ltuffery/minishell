/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:23:30 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/27 16:04:51 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char	*var_replace(char *line, char *var_env)
{
	char	*new;
	int		i;

	new = malloc(ft_strlen(line) + 1);
	if (new == NULL)
		return (line);
	i = ft_strfind(line, '=');
	ft_strlcpy(new, line, ft_strlen(line) + 1);
	if (i == -1)
		ft_strjoin(new, "=");
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

void	modif_var(char *line, t_data *data)
{
	char	*var;
	char	*value;
	int		i;

	var = getvar(line);
	i = 0;
	while (!var_is_equal(var, data->env[i]))
		i++;
	if (!remove_plus(line))
	{
		value = getvalue(data->env, var);
		if (value == NULL || ft_strchr(line, '=') != NULL)
			data->env[i] = var_replace(line, data->env[i]);
		if (value != NULL)
			free(value);
	}
	else
		data->env[i] = var_append(line, data->env[i]);
	free(var);
}

void	arg_handler(char **cmd, t_data *data)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!parsing_var(cmd[i]))
		{
			if (!existing_var(cmd[i], data->env))
			{
				remove_plus(cmd[i]);
				data->env = ft_strappend(cmd[i], data->env);
			}
			else
				modif_var(cmd[i], data);
		}
		i++;
	}
}

int	export_builtins(char **cmd, t_data *data)
{
	char	**tmp;

	if (ft_count(cmd) == 1)
	{
		tmp = arr_cpy(data->env);
		print_by_order(tmp);
	}
	else
		arg_handler(cmd, data);
	return (0);
}
