/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:07:27 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 12:16:29 by njegat           ###   ########.fr       */
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

void	open_files(t_data *data)
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
			data->fd_infile = tmp->fd;
		}
		else if (tmp->type == OUTFILE || tmp->type == APPEND)
		{
			if (tmp->type == OUTFILE)
				tmp->fd = open(tmp->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			else if (tmp->type == APPEND)
				tmp->fd = open(tmp->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			data->fd_outfile = tmp->fd;
		}
		tmp = tmp->next;
	}
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
		dup2(0, data->fd_infile);
	if (data->fd_outfile >= 0)
		dup2(1, data->fd_outfile);
}

void	exec_builtins_handler(t_data *data, t_env *my_env)
{
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
}

void	single_cmd(t_data *data, t_env *my_env)
{
	char	**builtins;
	int		i;

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
	//exec_cmd_single();
}

void	exec_redirect(t_data *data, t_env *my_env)
{
	if (!data->next)
		single_cmd(data, my_env);
}
