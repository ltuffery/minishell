/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitcode_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:58:07 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/27 04:08:45 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exitcode	*exitcode(void)
{
	static t_exitcode	*exitcode;

	if (exitcode == NULL)
	{
		exitcode = malloc(sizeof(t_exitcode));
		exitcode->code = 0;
		exitcode->write_by_signale = FALSE;
	}
	return (exitcode);
}

void	set_code(int code, t_boolean is_set_by_signal)
{
	t_exitcode	*instance;

	instance = exitcode();
	instance->code = code;
	instance->write_by_signale = is_set_by_signal;
}

void	set_if_sig_false(int code)
{
	t_exitcode	*instance;

	instance = exitcode();
	if (!instance->write_by_signale)
		instance->code = code;
	instance->write_by_signale = FALSE;
}
