/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:28:44 by njegat            #+#    #+#             */
/*   Updated: 2023/05/17 13:03:38 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/utils.h"

static char	**get_path(char **env)
{
	char	*path;
	char	**output;

	path = getvalue(env, "PATH");
	if (!path)
		return (NULL);
	output = ft_split(path, ':');
	free(path);
	return (output);
}

static int	check_error(t_cmd *cmd)
{
	if (!cmd->arg[0][0])
		return (1);
	if (ft_strfind(cmd->arg[0], '/') && access(cmd->arg[0], X_OK) == 0)
		return (1);
	return (0);
}

int	get_cmd_path(t_data *data, t_cmd *cmd)
{
	char	**path;
	int		i;

	if (check_error(cmd))
		return (0);
	path = get_path(data->env);
	if (!path)
		return (1);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd->arg[0]);
		if (access(path[i], X_OK) == 0)
		{
			free(cmd->arg[0]);
			cmd->arg[0] = ft_strdup(path[i]);
			ft_double_free(path);
			return (0);
		}
		i++;
	}
	ft_double_free(path);
	return (-1);
}
