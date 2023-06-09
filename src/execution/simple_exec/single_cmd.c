/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:15:28 by njegat            #+#    #+#             */
/*   Updated: 2023/05/17 16:39:19 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"
#include "../../../include/builtins.h"
#include "../../../include/utils.h"
#include "../../../include/signals.h"
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

static void	launch_cmd(t_data *data, int error_path)
{
	if (data->cmd->arg[0])
	{
		if (access(data->cmd->arg[0], X_OK) == 0 && error_path >= 0)
		{
			simple_dup_handler(data->cmd);
			close_files(data->cmd);
			if (execve(data->cmd->arg[0], data->cmd->arg, data->env) == -1)
			{
				perror("execve");
				free_struct(&data->cmd);
				ft_double_free(data->env);
				free(exitcode());
				if (errno == EACCES)
					exit(126);
				exit(1);
			}
		}
		ft_print_error_cmd(data->cmd->arg[0], error_path, data);
	}
	else
		ft_print_error_cmd("''", error_path, data);
}

static void	exec_cmd_single(t_data *data)
{
	int	error_path;
	int	err_file;
	int	exit_status;

	error_path = get_cmd_path(data, data->cmd);
	err_file = open_heredoc(data);
	if (exitcode()->write_by_signale == TRUE)
		return ;
	if (!err_file)
		err_file = open_files(data->cmd);
	if (!err_file)
	{
		data->cmd->child = fork();
		if (data->cmd->child == 0)
		{
			init_signals(DEFAULT);
			launch_cmd(data, error_path);
		}
		init_signals(CHILD);
	}
	waitpid(data->cmd->child, &exit_status, 0);
	set_if_sig_false(WEXITSTATUS(exit_status));
	init_signals(PARENT);
	close_files(data->cmd);
}

static void	exec_builtins(t_data *data, int tmp_in, int tmp_out)
{
	int	status;

	status = 0;
	if (!strcmp_strict(data->cmd->arg[0], "cd"))
		status = cd_builtins(data, data->cmd->arg);
	else if (!strcmp_strict(data->cmd->arg[0], "echo"))
		status = echo_builtins(data->cmd->arg);
	else if (!strcmp_strict(data->cmd->arg[0], "env"))
		status = env_builtins(data->env);
	else if (!strcmp_strict(data->cmd->arg[0], "exit"))
	{
		close_files(data->cmd);
		close(tmp_in);
		close(tmp_out);
		status = exit_builtins(data, data->cmd->arg);
	}
	else if (!strcmp_strict(data->cmd->arg[0], "export"))
		status = export_builtins(data->cmd->arg, data);
	else if (!strcmp_strict(data->cmd->arg[0], "pwd"))
		status = pwd_builtins();
	else if (!strcmp_strict(data->cmd->arg[0], "unset"))
		status = unset_builtins(data, data->cmd->arg);
	set_code(status, FALSE);
}

static void	exec_builtins_handler(t_data *data)
{
	int	tmp_out;
	int	tmp_in;
	int	err_file;

	err_file = open_heredoc(data);
	if (exitcode()->write_by_signale == TRUE)
		return ;
	if (!err_file)
		err_file = open_files(data->cmd);
	if (!err_file)
	{
		tmp_out = dup(1);
		tmp_in = dup(0);
		simple_dup_handler(data->cmd);
		exec_builtins(data, tmp_in, tmp_out);
		dup2(tmp_out, 1);
		dup2(tmp_in, 0);
		close(tmp_out);
		close(tmp_in);
	}
	close_files(data->cmd);
}

void	single_cmd(t_data *data)
{
	if (!data->cmd->arg)
	{
		open_heredoc(data);
		if (exitcode()->write_by_signale == TRUE)
			return ;
		open_files(data->cmd);
		close_files(data->cmd);
		return ;
	}
	if (is_builtins(data->cmd) == TRUE)
		exec_builtins_handler(data);
	else
		exec_cmd_single(data);
}
