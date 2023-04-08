/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_dup_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 08:29:41 by njegat            #+#    #+#             */
/*   Updated: 2023/04/08 08:30:44 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"

static int	dup_even(t_data *data, t_cmd *cmd, int pos)
{
	int	err_dup;

	err_dup = 0;
	if (cmd->fd_infile != -1)
		err_dup = dup2(cmd->fd_infile, 0);
	else if (pos != 0)
		err_dup = dup2(data->pipefd2[0], 0);
	if (err_dup == -1)
		return (ERR_DUP);
	if (cmd->fd_outfile != -1)
		err_dup = dup2(cmd->fd_outfile, 1);
	else if (cmd->next)
		err_dup = dup2(data->pipefd1[1], 1);
	if (err_dup == -1)
		return (ERR_DUP);
	return (0);
}

static int	dup_odd(t_data *data, t_cmd *cmd)
{
	int	err_dup;

	err_dup = 0;
	if (cmd->fd_infile != -1)
		err_dup = dup2(cmd->fd_infile, 0);
	else
		err_dup = dup2(data->pipefd1[0], 0);
	if (err_dup == -1)
		return (ERR_DUP);
	if (cmd->fd_outfile != -1)
		err_dup = dup2(cmd->fd_outfile, 1);
	else if (cmd->next)
		err_dup = dup2(data->pipefd2[1], 1);
	if (err_dup == -1)
		return (ERR_DUP);
	return (0);
}

void	pipe_dup_handler(t_data *data, t_cmd *cmd, int pos)
{
	int	err_dup;

	if (pos % 2 == EVEN)
	{
		err_dup = dup_even(data, cmd, pos);
		if (err_dup)
			exit_fork(data);
	}
	else
	{
		err_dup = dup_odd(data, cmd);
		if (err_dup)
			exit_fork(data);
	}
}
