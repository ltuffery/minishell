/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:57:37 by njegat            #+#    #+#             */
/*   Updated: 2023/04/07 17:50:09 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"
#include "../../../include/signals.h"
#include "../../../include/utils.h"

void	close_pipe(t_data *data, t_cmd *cmd, int pos)
{
	if (pos == 0)
	{
		close(data->pipefd1[0]);
		close(data->pipefd1[1]);
	}
	else if (!cmd->next)
	{
		if (pos % 2 == EVEN)
			close(data->pipefd2[0]);
		else
			close(data->pipefd1[0]);
	}
	else
	{
		close(data->pipefd1[0]);
		close(data->pipefd1[1]);
		close(data->pipefd2[0]);
		close(data->pipefd2[1]);
	}
}

void	close_all_files(t_data *data)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = data->cmd;
	while (tmp_cmd)
	{
		close_files(tmp_cmd);
		tmp_cmd = tmp_cmd->next;
	}
}

void	exit_fork(t_data *data)
{
	free_struct(&data->cmd);
	ft_double_free(data->env);
	close_pipe(data, data->cmd, 1);
	perror("minishoul: ");
	exit(1);
}

int	dup_even(t_data *data, t_cmd *cmd, int pos)
{
	int	err_dup;

	err_dup = 0;
	if (cmd->fd_infile != -1)
		err_dup = dup2(cmd->fd_infile, 0);
	else if (pos != 0)
		err_dup = dup2(data->pipefd2[0], 0);
	if (err_dup == -1)
		return (ERR_DUP);
	if (cmd->fd_outfile != -1)
		err_dup = dup2(cmd->fd_outfile, 1);
	else if (cmd->next)
		err_dup = dup2(data->pipefd1[1], 1);
	if (err_dup == -1)
		return (ERR_DUP);
	return (0);
}

int	dup_odd(t_data *data, t_cmd *cmd)
{
	int	err_dup;

	err_dup = 0;
	if (cmd->fd_infile != -1)
		err_dup = dup2(cmd->fd_infile, 0);
	else
		err_dup = dup2(data->pipefd1[0], 0);
	if (err_dup == -1)
		return (ERR_DUP);
	if (cmd->fd_outfile != -1)
		err_dup = dup2(cmd->fd_outfile, 1);
	else if (cmd->next)
		err_dup = dup2(data->pipefd2[1], 1);
	if (err_dup == -1)
		return (ERR_DUP);
	return (0);
}

void	dup_handler(t_data *data, t_cmd *cmd, int pos)
{
	int	err_dup;

	if (pos % 2 == EVEN)
	{
		err_dup = dup_even(data, cmd, pos);
		if (err_dup)
			exit_fork(data);
	}
	else
	{
		err_dup = dup_odd(data, cmd);
		if (err_dup)
			exit_fork(data);
	}
}

void	exec_pipe(t_data *data, t_cmd *cmd, int pos)
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
				close_pipe(data, cmd, pos);
				close_all_files(data);
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
