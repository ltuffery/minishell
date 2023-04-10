/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitcode_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:58:07 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/07 16:32:18 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_code(int code, t_boolean is_set_by_signal)
{
	g_status.code = code;
	g_status.write_by_signale = is_set_by_signal;
}

void	set_if_sig_false(int code)
{
	if (! g_status.write_by_signale)
		g_status.code = code;
	g_status.write_by_signale = FALSE;
}
