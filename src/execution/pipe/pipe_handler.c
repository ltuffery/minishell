/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:57:37 by njegat            #+#    #+#             */
/*   Updated: 2023/04/08 09:44:43 by njegat           ###   ########.fr       */
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
					exit (1);
				}
			}
			ft_print_error_cmd(cmd->arg[0], err_path);
		}
		else
			ft_print_error_cmd("''", err_path);
	}
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
