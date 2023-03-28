/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:21:44 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 18:33:39 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/utils.h"

void	simple_dup_handler(t_data *data)
{
	if (data->fd_infile >= 0)
		if (dup2(data->fd_infile, 0))
			perror("minishoul: dup2");
	if (data->fd_outfile >= 0)
		if (dup2(data->fd_outfile, 1))
			perror("minishoul: dup2");
}

void	ft_print_error_cmd(char *cmd, int error_path)
{
	if (ft_strfind(cmd, '/') || error_path == 1)
	{
		write(2, "minishoul: ", 7);
		write(2, cmd, ft_strlen(cmd));
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
	{
		write(2, "minishoul: ", 7);
		write(2, cmd, ft_strlen(cmd));
		ft_putendl_fd(": command not found", 2);
	}
}

int	get_cmd_path(t_data *data, t_env *my_env)
{
	char	*path;
	char	**tmp_path;
	int		i;
	char	*output;

	path = getvalue(my_env->loc_env, "PATH");
	if (!path)
		return (1);
	tmp_path = ft_split(path, ':');
	free(path);
	i = 0;
	while (tmp_path[i])
	{
		output = ft_strdup(tmp_path[i]);
		output = ft_strjoin(output, "/");
		output = ft_strjoin(output, data->cmdx[0]);
		if (access(output, X_OK) == 0)
		{
			free(data->cmdx[0]);
			data->cmdx[0] = output;
			break ;
		}
		free(output);
		i++;
	}
	return (0);
}
