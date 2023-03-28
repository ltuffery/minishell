/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:15:28 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 18:34:07 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"
#include "../../../include/utils.h"

static int	strcmp_strict(char *s1, char *s2)
{
	int	i;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (ft_strlen(s1) - ft_strlen(s2));
	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	exec_cmd_single(t_data *data, t_env *my_env)
{
	int	error_path;
	error_path = get_cmd_path(data, my_env);
	if (!open_files(data))
	{
		pid_t child = fork();
		if (child == 0)
		{
			if (data->cmdx[0])
			{
				if (access(data->cmdx[0], X_OK) == 0)
				{
					simple_dup_handler(data);
					close_files(data);
					if (execve(data->cmdx[0], data->cmdx, my_env->loc_env) == -1)
					{
						perror("execve");
						free_struct(&data);
						exit (1);
					}
				}
				ft_print_error_cmd(data->cmdx[0], error_path);
			}
			else
				ft_print_error_cmd("''", error_path);
			free_struct(&data);
			exit (1);
		}
	}
	waitpid(-1, NULL, 0);
	close_files(data);
}

void	exec_builtins_handler(t_data *data, t_env *my_env)
{
	int	tmp_out;
	int	tmp_in;
	
	tmp_out = dup(1);
	tmp_in = dup(0);
	open_files(data);
	simple_dup_handler(data);
	if (!strcmp_strict(data->cmdx[0], "cd"))
		cd_builtins("/");
	else if (!strcmp_strict(data->cmdx[0], "echo"))
		echo_builtins(data->cmdx);
	else if (!strcmp_strict(data->cmdx[0], "env"))
		env_builtins(my_env->loc_env);
	else if (!strcmp_strict(data->cmdx[0], "exit"))
		exit_builtins();
	else if (!strcmp_strict(data->cmdx[0], "export"))
		export_builtins(data->cmdx, my_env);
	else if (!strcmp_strict(data->cmdx[0], "pwd"))
		pwd_builtins();
	// else if (!strcmp_strict(data->cmdx[0], "unset"))
	// 	unset_builtins();
	close_files(data);
	dup2(tmp_out, 1);
	dup2(tmp_in, 0);
	close(tmp_out);
	close(tmp_in);
}

void	single_cmd(t_data *data, t_env *my_env)
{
	char	**builtins;
	int		i;

	if (!data->cmdx)
	{
		open_files(data);
		close_files(data);
		return ;
	}
	builtins = ft_split("cd:echo:env:exit:export:pwd:unset", ':');
	i = 0;
	while (builtins[i])
	{
		if (!strcmp_strict(data->cmdx[0], builtins[i]))
		{
			exec_builtins_handler(data, my_env);
			ft_double_free(builtins);
			return ;
		}
		i++;
	}
	ft_double_free(builtins);
	exec_cmd_single(data, my_env);
}
