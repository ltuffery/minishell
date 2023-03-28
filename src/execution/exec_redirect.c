/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:07:27 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 14:21:25 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
# include <fcntl.h>

int	strcmp_strict(char *s1, char *s2)
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

int	open_files(t_data *data)
{
	t_file	*tmp;

	tmp = data->file;
	while (tmp)
	{
		if (tmp->type == INFILE || tmp->type == HERE_DOC)
		{
			if (tmp->type == INFILE)
				tmp->fd = open(tmp->name, O_RDONLY, 0644);
		//	else if (tmp->type == HERE_DOC)
		//		tmp->fd = get_here_doc();
			if (tmp->fd == -1)
			{
				perror("minishoull ");
				return (1);
			}
			data->fd_infile = tmp->fd;
		}
		else if (tmp->type == OUTFILE || tmp->type == APPEND)
		{
			if (tmp->type == OUTFILE)
				tmp->fd = open(tmp->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			else if (tmp->type == APPEND)
				tmp->fd = open(tmp->name, O_APPEND | O_CREAT | O_WRONLY, 0644);
			if (tmp->fd == -1)
				perror("minishoull ");
			data->fd_outfile = tmp->fd;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	close_files(t_data *data)
{
	t_file	*tmp;

	tmp = data->file;
	while (tmp)
	{
		close(tmp->fd);
		tmp = tmp->next;
	}
}

void	dup_handler(t_data *data)
{
	if (data->fd_infile >= 0)
		dup2(data->fd_infile, 0);
	if (data->fd_outfile >= 0)
		dup2(data->fd_outfile, 1);
}

void	exec_builtins_handler(t_data *data, t_env *my_env)
{
	int	tmp_out;
	int	tmp_in;
	
	tmp_out = dup(1);
	tmp_in = dup(0);
	open_files(data);
	dup_handler(data);
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

int	get_cmd_path(t_data *data, t_env *my_env)
{
	char	*path;
	char	**tmp_path;
	int		i;
	char	*output;

	path = getvalue(my_env->loc_env, "PATH");
	if (!path)
		return (1);
	tmp_path = ft_split(path, ':');
	free(path);
	i = 0;
	while (tmp_path[i])
	{
		output = ft_strdup(tmp_path[i]);
		output = ft_strjoin(output, "/");
		output = ft_strjoin(output, data->cmdx[0]);
		if (access(output, X_OK) == 0)
		{
			free(data->cmdx[0]);
			data->cmdx[0] = output;
			break ;
		}
		free(output);
		i++;
	}
	return (0);
}

void	ft_print_error_cmd(char *cmd, int error_path)
{
	if (ft_strfind(cmd, '/') || error_path == 1)
	{
		write(2, "pipex: ", 7);
		write(2, cmd, ft_strlen(cmd));
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
	{
		write(2, "pipex: ", 7);
		write(2, cmd, ft_strlen(cmd));
		ft_putendl_fd(": command not found", 2);
	}
}

# include <sys/wait.h>

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
					dup_handler(data);
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

void	exec_redirect(t_data *data, t_env *my_env)
{
	if (!data->next)
		single_cmd(data, my_env);
}
