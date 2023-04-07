/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:05:01 by njegat            #+#    #+#             */
/*   Updated: 2023/04/07 17:06:25 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"

static int	init_pipe(t_data *data, t_cmd *cmd, int pos)
{
	int	error;
	
	if (pos == 0)
	{
		error = pipe(data->pipefd1);
		if (error == -1)
			return (ERR_PIPE);
	}
	else if (pos % 2 == EVEN && cmd->next)
	{
		close(data->pipefd1[0]);
		close(data->pipefd1[1]);
		error = pipe(data->pipefd1);
		if (error == -1)
			return (ERR_PIPE);
	}
	else if (pos % 2 == ODD && cmd->next)
	{
		if (pos > 1)
		{
			close(data->pipefd2[0]);
			close(data->pipefd2[1]);
		}
		error = pipe(data->pipefd2);
		if (error == -1)
			return (ERR_PIPE);
	}
	return (0);
}

int	select_pipe(t_data *data, t_cmd *cmd, int pos)
{
	int	error;
	
	if (pos == 0)
		error = init_pipe(data, cmd, pos);
	else if (!cmd->next && pos > 1)
	{
		close(data->pipefd2[1]);
		close(data->pipefd1[1]);
		if (pos % 2 == EVEN)
			close(data->pipefd1[0]);
		else
			close(data->pipefd2[0]);
	}
	else if (!cmd->next && pos == 1)
		close(data->pipefd1[1]);
	else
		error = init_pipe(data, cmd, pos);
	return (0);
}
