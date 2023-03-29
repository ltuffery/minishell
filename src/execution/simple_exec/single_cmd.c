/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:15:28 by njegat            #+#    #+#             */
/*   Updated: 2023/03/29 16:55:40 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"
#include "../../../include/utils.h"

void	launch_cmd(t_cmd *cmd, t_env *my_env, int error_path)
{
	if (cmd->arg[0])
	{
		if (access(cmd->arg[0], X_OK) == 0)
		{
			simple_dup_handler(cmd);
			close_files(cmd);
			if (execve(cmd->arg[0], cmd->arg, my_env->loc_env) == -1)
			{
				perror("execve");
				free_struct(&cmd);
				exit (1);
			}
		}
		ft_print_error_cmd(cmd->arg[0], error_path);
	}
	else
		ft_print_error_cmd("''", error_path);
}

void	exec_cmd_single(t_cmd *cmd, t_env *my_env)
{
	int	error_path;
	int	err_file;

	error_path = get_cmd_path(cmd, my_env);
	err_file = open_files(cmd);
	if (!err_file)
	{
		cmd->child = fork();
		if (cmd->child == 0)
		{
			launch_cmd(cmd, my_env, error_path);
			free_struct(&cmd);
			exit (1);
		}
	}
	waitpid(-1, NULL, 0);
	close_files(cmd);
}

void	exec_builtins(t_cmd *cmd, t_env *my_env)
{
	if (!strcmp_strict(cmd->arg[0], "cd"))
		cd_builtins("/");
	else if (!strcmp_strict(cmd->arg[0], "echo"))
		echo_builtins(cmd->arg);
	else if (!strcmp_strict(cmd->arg[0], "env"))
		env_builtins(my_env->loc_env);
	else if (!strcmp_strict(cmd->arg[0], "exit"))
		exit_builtins();
	else if (!strcmp_strict(cmd->arg[0], "export"))
		export_builtins(cmd->arg, my_env);
	else if (!strcmp_strict(cmd->arg[0], "pwd"))
		pwd_builtins();
	// else if (!strcmp_strict(cmd->arg[0], "unset"))
	// 	unset_builtins();
}

void	exec_builtins_handler(t_cmd *cmd, t_env *my_env)
{
	int	tmp_out;
	int	tmp_in;
	int	err_file;

	err_file = open_files(cmd);
	if (!err_file)
	{
		tmp_out = dup(1);
		tmp_in = dup(0);
		simple_dup_handler(cmd);
		exec_builtins(cmd, my_env);
		close_files(cmd);
		dup2(tmp_out, 1);
		dup2(tmp_in, 0);
		close(tmp_out);
		close(tmp_in);
	}
}

void	single_cmd(t_cmd *cmd, t_env *my_env)
{
	char	**builtins;
	int		i;

	if (!cmd->arg)
	{
		open_files(cmd);
		close_files(cmd);
		return ;
	}
	builtins = ft_split("cd:echo:env:exit:export:pwd:unset", ':');
	i = 0;
	while (builtins[i])
	{
		if (!strcmp_strict(cmd->arg[0], builtins[i]))
		{
			exec_builtins_handler(cmd, my_env);
			ft_double_free(builtins);
			return ;
		}
		i++;
	}
	ft_double_free(builtins);
	exec_cmd_single(cmd, my_env);
}
