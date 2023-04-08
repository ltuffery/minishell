/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:06:35 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/08 19:36:30 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/utils.h"

void	exit_builtins(t_data *data)
{
	ft_putendl_fd("exit", 1);
	free_struct(&data->cmd);
	ft_double_free(data->env);
	exit(g_status.code);
}
