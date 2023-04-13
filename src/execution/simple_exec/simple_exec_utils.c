/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 08:35:09 by njegat            #+#    #+#             */
/*   Updated: 2023/04/13 14:21:10 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"

void	simple_dup_handler(t_cmd *cmd)
{
	if (cmd->fd_infile >= 0)
		if (dup2(cmd->fd_infile, 0) == -1)
			perror("minishoul: dup2");
	if (cmd->fd_outfile >= 0)
		if (dup2(cmd->fd_outfile, 1) == -1)
			perror("minishoul: dup2");
}
