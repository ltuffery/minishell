/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:07:27 by njegat            #+#    #+#             */
/*   Updated: 2023/04/04 21:32:12 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

void	exec_handler(t_data *data)
{
	if (!data->cmd->next)
		single_cmd(data);
	else
		pipe_handler(data);
}
