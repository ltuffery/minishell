/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:23:30 by ltuffery          #+#    #+#             */
/*   Updated: 2023/05/03 18:10:47 by njegat           ###   ########.fr       */
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

	new = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (new == NULL)
		return (line);
	i = ft_strfind(line, '=');
	ft_strlcpy(new, line, ft_strlen(line) + 1);
	if (i == 0)
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
	new[j] = 0;
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

int	arg_handler(char **cmd, t_data *data)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
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
		else
			error = 1;
		i++;
	}
	return (error);
}

int	export_builtins(char **cmd, t_data *data)
{
	char	**tmp;
	int		error;

	error = 0;
	if (ft_count(cmd) == 1)
	{
		tmp = arr_cpy(data->env);
		print_by_order(tmp);
	}
	else
		error = arg_handler(cmd, data);
	return (error);
}
