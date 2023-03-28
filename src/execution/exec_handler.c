/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:07:27 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 15:31:45 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"



void	exec_handler(t_data *data, t_env *my_env)
{
	if (!data->next)
		single_cmd(data, my_env);
}
