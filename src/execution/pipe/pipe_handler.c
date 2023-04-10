/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:57:37 by njegat            #+#    #+#             */
/*   Updated: 2023/04/10 17:57:52 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"
#include "../../../include/signals.h"
#include "../../../include/utils.h"
#include "../../../include/builtins.h"

void	exec_pipe(t_data *data, t_cmd *cmd, int pos)
{
	int err_path;

	err_path = get_cmd_path(data, cmd);
	cmd->child = fork();
	if (cmd->child == 0)
	{
		init_signals(DEFAULT);
		if (cmd->arg[0])
		{
			if (access(cmd->arg[0], X_OK) == 0)
			{
				pipe_dup_handler(data, cmd, pos);
				close_pipe(data, cmd, pos);
				close_all_files(data);
				if (execve(cmd->arg[0], cmd->arg, data->env) == -1)
				{
					perror("execve");
					free_struct(&data->cmd);
					ft_double_free(data->env);
					exit (1);
				}
			}
			ft_print_error_cmd(cmd->arg[0], err_path);
		}
		else
			ft_print_error_cmd("''", err_path);
	}
	init_signals(CHILD);
}

void	launch_builtins(t_data *data, t_cmd *cmd)
{
	if (!strcmp_strict(cmd->arg[0], "cd"))
		cd_builtins(data, cmd->arg);
	else if (!strcmp_strict(cmd->arg[0], "echo"))
		echo_builtins(cmd->arg);
	else if (!strcmp_strict(cmd->arg[0], "env"))
		env_builtins(data->env);
	else if (!strcmp_strict(cmd->arg[0], "exit"))
		exit_builtins(data);
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
		exit(0);
	}
}

int	launch_handler(t_data *data, t_cmd *cmd, int pos)
{
	int	error;

	error = select_pipe(data, cmd, pos);
	if (is_builtins(cmd) == TRUE)
		exec_pipe_builtins(data, cmd, pos);
	else
		exec_pipe(data, cmd, pos);
	return (0);
}

static void	close_end_pipe(t_data *data, int pos)
{
	if (pos % 2)
		close(data->pipefd2[0]);
	else
		close(data->pipefd1[0]);
}

int	pipe_handler(t_data *data)
{
	t_cmd	*cmd;
	int		error;
	int		pos;
	int		exit_status;
	pid_t	child;
	
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
		child = cmd->child;
		cmd = cmd->next;
		pos++;
	}
	close_end_pipe(data, pos);
	waitpid(child, &exit_status, 0);
	set_if_sig_false(WEXITSTATUS(exit_status));
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
	init_signals(PARENT);
return (0);
}
