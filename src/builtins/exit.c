/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:06:35 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/18 15:23:13 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/utils.h"

void	exit_builtins(t_data *data)
{
	int	code;

	ft_putendl_fd("exit", 1);
	free_struct(&data->cmd);
	ft_double_free(data->env);
	code = exitcode()->code;
	free(exitcode());
	exit(code);
}
