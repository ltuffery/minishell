/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:57:37 by njegat            #+#    #+#             */
/*   Updated: 2023/04/07 17:05:17 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"
#include "../../../include/signals.h"
#include "../../../include/utils.h"



exec_pipe(t_data *data, t_cmd *cmd, int pos)
{
	int err_path;

	err_path = get_cmd_path(data, cmd);
	cmd->child = fork();
	if (cmd->child == 0)
	{
		if (cmd->arg[0])
		{
			if (access(cmd->arg[0], X_OK) == 0)
			{
				dup_handler(data, cmd, pos);
				//close_pipe(data, pos);
				close_files(cmd);
				if (execve(cmd->arg[0], cmd->arg, data->env) == -1)
				{
					perror("execve");
					free_struct(&data->cmd);
					exit (1);
				}
			}
		}
	}
}

int	launch_handler(t_data *data, t_cmd *cmd, int pos)
{
	int	error;

	error = select_pipe(data, cmd, pos);
	exec_pipe(data, cmd, pos);
	return (0);
}

int	pipe_handler(t_data *data)
{
	t_cmd	*cmd;
	int		error;
	int		pos;
	
	error = open_heredoc(data);
	if (error)
		return (ERR_FILE);
	cmd = data->cmd;
	pos = 0;
	while (cmd)
	{
		error = open_files(cmd);
		if (!error)
		{
			launch_handler(data, cmd, pos);
		}
		close_files(cmd);
		cmd = cmd->next;
		pos++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
return (0);
}
