/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:57:37 by njegat            #+#    #+#             */
/*   Updated: 2023/04/07 06:06:40 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execute.h"

void	pipe_handler(t_data *data)
{
	t_cmd	*cmd;
	int		error_file;
	
	error_file = open_heredoc(data);
	if (error_file)
		return ;
	cmd = data->cmd;
	while (cmd)
	{
		error_file = open_files(cmd);
		if (!error_file)
		{
			
		}
		cmd = cmd->next;
	}
}