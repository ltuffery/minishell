/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:21:44 by njegat            #+#    #+#             */
/*   Updated: 2023/05/03 16:20:18 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/utils.h"

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

int	is_builtins(t_cmd *cmd)
{
	char	**builtins;
	int		i;

	builtins = ft_split("cd:echo:env:exit:export:pwd:unset", ':');
	i = 0;
	while (builtins[i])
	{
		if (!strcmp_strict(cmd->arg[0], builtins[i]))
		{
			ft_double_free(builtins);
			return (TRUE);
		}
		i++;
	}
	ft_double_free(builtins);
	return (FALSE);
}

void	ft_print_error_cmd(char *cmd, int error_path, t_data *data)
{
	if (ft_strfind(cmd, '/') || error_path == 1)
	{
		ft_putstr_fd("minishoul: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		close_files(data->cmd);
		free_struct(&data->cmd);
		ft_double_free(data->env);
		free(exitcode());
		exit(126);
	}
	else
	{
		ft_putstr_fd("minishoul: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		close_files(data->cmd);
		free_struct(&data->cmd);
		ft_double_free(data->env);
		free(exitcode());
		exit(127);
	}
}

void	ft_print_error_file(char *file)
{
	ft_putstr_fd("minishoul: ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	ft_print_error_ambiguous(void)
{
	ft_putendl_fd("minishoul: ambiguous redirect", 2);
}
