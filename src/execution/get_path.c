/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:28:44 by njegat            #+#    #+#             */
/*   Updated: 2023/05/16 07:14:52 by njegat           ###   ########.fr       */
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

// int	check_absolute_path(t_cmd *cmd)
// {
// 	char	*tmp;
// 	int		jump;
// 	int		error;

// 	error = 0;
// 	if (ft_strfind(cmd->arg[0], '/'))
// 	{
// 		if (access(cmd->arg[0], X_OK) == 0)
// 		{
// 			tmp = ft_strdup(cmd->arg[0]);
// 			jump = 0;
// 			while (tmp)
// 			{
// 				if (tmp[0] != '.' || tmp[1] != '/')
// 					break ;
// 				jump += 2;
// 				free(tmp);
// 				tmp = ft_strdup(cmd->arg[0] + jump);
// 			}
// 			if (!tmp)
// 				error = 1;
// 			else if (!tmp[0])
// 				error = 1;
// 			else
// 			{
// 				free(cmd->arg[0]);
// 				cmd->arg[0] = ft_strdup(tmp);
// 			}
// 			if (!cmd->arg[0])
// 				error = 1;
// 		}
// 	}
// 	return (error);
// }

// int	check_absolute_path(t_cmd *cmd)
// {
// 	char	*tmp;
// 	int		jump;
// 	int		error;

// 	error = 0;
// 	if (ft_strfind(cmd->arg[0], '/'))
// 	{
// 		if (access(cmd->arg[0], X_OK) == 0)
// 		{
// 			jump = skip_set(cmd->arg[0], "./");
// 			tmp = strdup(cmd->arg[0]);
// 			if (!tmp)
// 				return (1);
// 			free(cmd->arg[0]);
// 			cmd->arg[0] = tmp;
// 		}
// 	}
// 	return (error);
// }

int	get_cmd_path(t_data *data, t_cmd *cmd)
{
	char	**path;
	int		i;

	if (!cmd->arg[0][0])
		return (0);
	if (ft_strfind(cmd->arg[0], '/') && access(cmd->arg[0], X_OK) == 0)
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
			break ;
		}
		i++;
	}
	ft_double_free(path);
	return (0);
}
