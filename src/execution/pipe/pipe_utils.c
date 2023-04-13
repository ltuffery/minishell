/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 08:26:58 by njegat            #+#    #+#             */
/*   Updated: 2023/04/13 12:56:36 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"
#include "../../../include/utils.h"

void	close_pipe(t_data *data, t_cmd *cmd, int pos)
{
	if (pos == 0)
	{
		close(data->pipefd1[0]);
		close(data->pipefd1[1]);
	}
	else if (!cmd->next)
	{
		if (pos % 2 == EVEN)
			close(data->pipefd2[0]);
		else
			close(data->pipefd1[0]);
	}
	else
	{
		close(data->pipefd1[0]);
		close(data->pipefd1[1]);
		close(data->pipefd2[0]);
		close(data->pipefd2[1]);
	}
}

void	close_end_pipe(t_data *data, int pos)
{
	if (pos % 2)
		close(data->pipefd2[0]);
	else
		close(data->pipefd1[0]);
}

void	close_all_files(t_data *data)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = data->cmd;
	while (tmp_cmd)
	{
		close_files(tmp_cmd);
		tmp_cmd = tmp_cmd->next;
	}
}

void	exit_fork(t_data *data)
{
	free_struct(&data->cmd);
	ft_double_free(data->env);
	close_pipe(data, data->cmd, 1);
	perror("minishoul: ");
	exit(1);
}
