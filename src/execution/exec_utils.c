/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:21:44 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 18:43:05 by ltuffery         ###   ########.fr       */
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

void	simple_dup_handler(t_data *data)
{
	if (data->fd_infile >= 0)
		if (dup2(data->fd_infile, 0) == -1)
			perror("minishoul: dup2");
	if (data->fd_outfile >= 0)
		if (dup2(data->fd_outfile, 1) == -1)
			perror("minishoul: dup2");
}

void	ft_print_error_cmd(char *cmd, int error_path)
{
	if (ft_strfind(cmd, '/') || error_path == 1)
	{
		ft_putstr_fd("minishoul: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
	{
		ft_putstr_fd("minishoul: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
}

void	ft_print_error_file(char *file)
{
	ft_putstr_fd("minishoul: ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": No such file or directory", 2);
}
