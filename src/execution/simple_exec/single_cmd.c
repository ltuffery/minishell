/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:15:28 by njegat            #+#    #+#             */
/*   Updated: 2023/04/07 07:22:09 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"
#include "../../../include/builtins.h"
#include "../../../include/utils.h"
#include "../../../include/signals.h"
#include <signal.h>
#include <stdlib.h>

static void	launch_cmd(t_data *data, int error_path)
{
	if (data->cmd->arg[0])
	{
		if (access(data->cmd->arg[0], X_OK) == 0)
		{
			simple_dup_handler(data->cmd);
			close_files(data->cmd);
			if (execve(data->cmd->arg[0], data->cmd->arg, data->env) == -1)
			{
				perror("execve");
				free_struct(&data->cmd);
				exit (1);
			}
		}
		ft_print_error_cmd(data->cmd->arg[0], error_path);
	}
	else
		ft_print_error_cmd("''", error_path);
}

static void	exec_cmd_single(t_data *data)
{
	int	error_path;
	int	err_file;
	int	exit_status;

	error_path = get_cmd_path(data, data->cmd);
	err_file = open_heredoc(data);
	if (!err_file)
		err_file = open_files(data->cmd);
	if (!err_file)
	{
		data->cmd->child = fork();
		if (data->cmd->child == 0)
		{
			init_signals(DEFAULT);
			launch_cmd(data, error_path);
			free_struct(&data->cmd);
			exit (1);
		}
		init_signals(CHILD);
	}
	waitpid(data->cmd->child, &exit_status, 0);
	g_status = WEXITSTATUS(exit_status);
	init_signals(PARENT);
	close_files(data->cmd);
}

static void	exec_builtins(t_data *data, int tmp_in, int tmp_out)
{
	if (!strcmp_strict(data->cmd->arg[0], "cd"))
		cd_builtins(data, data->cmd->arg);
	else if (!strcmp_strict(data->cmd->arg[0], "echo"))
		echo_builtins(data->cmd->arg);
	else if (!strcmp_strict(data->cmd->arg[0], "env"))
		env_builtins(data->env);
	else if (!strcmp_strict(data->cmd->arg[0], "exit"))
	{
		close_files(data->cmd);
		close(tmp_in);
		close(tmp_out);
		exit_builtins(data);
	}
	else if (!strcmp_strict(data->cmd->arg[0], "export"))
		export_builtins(data->cmd->arg, data);
	else if (!strcmp_strict(data->cmd->arg[0], "pwd"))
		pwd_builtins();
	// else if (!strcmp_strict(cmd->arg[0], "unset"))
	// 	unset_builtins();
}

static void	exec_builtins_handler(t_data *data)
{
	int	tmp_out;
	int	tmp_in;
	int	err_file;

	err_file = open_heredoc(data);
	if (!err_file)
		err_file = open_files(data->cmd);
	if (!err_file)
	{
		tmp_out = dup(1);
		tmp_in = dup(0);
		simple_dup_handler(data->cmd);
		exec_builtins(data, tmp_in, tmp_out);
		close_files(data->cmd);
		dup2(tmp_out, 1);
		dup2(tmp_in, 0);
		close(tmp_out);
		close(tmp_in);
	}
}

void	single_cmd(t_data *data)
{
	char	**builtins;
	int		i;

	if (!data->cmd->arg)
	{
		open_heredoc(data);
		open_files(data->cmd);
		close_files(data->cmd);
		return ;
	}
	builtins = ft_split("cd:echo:env:exit:export:pwd:unset", ':');
	i = 0;
	while (builtins[i])
	{
		if (!strcmp_strict(data->cmd->arg[0], builtins[i]))
		{
			ft_double_free(builtins);
			exec_builtins_handler(data);
			return ;
		}
		i++;
	}
	ft_double_free(builtins);
	exec_cmd_single(data);
}
