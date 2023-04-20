/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:58:41 by njegat            #+#    #+#             */
/*   Updated: 2023/04/20 20:27:58 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"
#include "../../../include/builtins.h"
#include "../../../include/signals.h"
#include "../../../include/utils.h"

static void	launch_cmd_pipe(t_data *data, t_cmd *cmd, int pos)
{
	int	err_exec;

	pipe_dup_handler(data, cmd, pos);
	close_pipe(data, cmd, pos);
	close_all_files(data);
	err_exec = execve(cmd->arg[0], cmd->arg, data->env);
	if (err_exec == -1)
	{
		perror("execve");
		free_struct(&data->cmd);
		ft_double_free(data->env);
		free(exitcode());
		exit (1);
	}
}

void	exec_pipe(t_data *data, t_cmd *cmd, int pos)
{
	int	err_path;

	err_path = get_cmd_path(data, cmd);
	cmd->child = fork();
	if (cmd->child == 0)
	{
		init_signals(DEFAULT);
		if (cmd->arg[0])
		{
			if (access(cmd->arg[0], X_OK) == 0)
				launch_cmd_pipe(data, cmd, pos);
			close_pipe(data, cmd, pos);
			ft_print_error_cmd(cmd->arg[0], err_path, data);
		}
		else
		{
			close_pipe(data, cmd, pos);
			ft_print_error_cmd("''", err_path, data);
		}
	}
	init_signals(CHILD);
}

static void	launch_builtins(t_data *data, t_cmd *cmd)
{
	if (!strcmp_strict(cmd->arg[0], "cd"))
		cd_builtins(data, cmd->arg);
	else if (!strcmp_strict(cmd->arg[0], "echo"))
		echo_builtins(cmd->arg);
	else if (!strcmp_strict(cmd->arg[0], "env"))
		env_builtins(data->env);
	else if (!strcmp_strict(cmd->arg[0], "exit"))
		exit_builtins(data, cmd->arg);
	else if (!strcmp_strict(cmd->arg[0], "export"))
		export_builtins(cmd->arg, data);
	else if (!strcmp_strict(cmd->arg[0], "pwd"))
		pwd_builtins();
	else if (!strcmp_strict(cmd->arg[0], "unset"))
		unset_builtins(data, cmd->arg);
	set_code(0, FALSE);
}

void	exec_pipe_builtins(t_data *data, t_cmd *cmd, int pos)
{
	cmd->child = fork();
	if (cmd->child == 0)
	{
		pipe_dup_handler(data, cmd, pos);
		close_pipe(data, cmd, pos);
		close_all_files(data);
		launch_builtins(data, cmd);
		free_struct(&data->cmd);
		ft_double_free(data->env);
		free(exitcode());
		exit(1);
	}
}
