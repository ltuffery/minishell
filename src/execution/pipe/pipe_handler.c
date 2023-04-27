/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:57:37 by njegat            #+#    #+#             */
/*   Updated: 2023/04/27 06:57:21 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"
#include "../../../include/signals.h"
#include "../../../include/utils.h"

static int	launch_handler(t_data *data, t_cmd *cmd, int pos)
{
	int	error;

	error = select_pipe(data, cmd, pos);
	if (cmd->arg)
	{
		if (is_builtins(cmd) == TRUE && !error)
			exec_pipe_builtins(data, cmd, pos);
		else if (!error)
			exec_pipe(data, cmd, pos);
		else
			perror("minishoul: pipe");
	}
	return (error);
}

pid_t	exec_all(t_data *data)
{
	t_cmd	*cmd;
	pid_t	last_child;
	int		pos;
	int		error;

	cmd = data->cmd;
	pos = 0;
	last_child = -1;
	while (cmd)
	{
		error = open_files(cmd);
		if (!error)
		{
			launch_handler(data, cmd, pos);
			last_child = cmd->child;
		}
		close_files(cmd);
		cmd = cmd->next;
		pos++;
	}
	close_end_pipe(data, pos);
	return (last_child);
}

int	pipe_handler(t_data *data)
{
	int		error;
	int		exit_status;
	pid_t	last_child;

	error = open_heredoc(data);
	if (exitcode()->write_by_signale == TRUE)
		return (1);
	if (error)
	{
		set_code(1, TRUE);
		return (ERR_FILE);
	}
	last_child = exec_all(data);
	set_code(0, FALSE);
	if (last_child > -1)
	{
		waitpid(last_child, &exit_status, 0);
		set_if_sig_false(WEXITSTATUS(exit_status));
	}
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
	init_signals(PARENT);
	return (0);
}
