/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:28:44 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 18:49:15 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/utils.h"

static char	**get_path(t_env *my_env)
{
	char	*path;
	char	**output;

	path = getvalue(my_env->loc_env, "PATH");
	if (!path)
		return (NULL);
	output = ft_split(path, ':');
	free(path);
	return (output);
}

int	get_cmd_path(t_data *data, t_env *my_env)
{
	char	**path;
	int		i;

	path = get_path(my_env);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], data->cmdx[0]);
		if (access(path[i], X_OK) == 0)
		{
			free(data->cmdx[0]);
			data->cmdx[0] = ft_strdup(path[i]);
			break ;
		}
		i++;
	}
	ft_double_free(path);
	return (0);
}
