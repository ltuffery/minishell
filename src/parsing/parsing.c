/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:36:00 by njegat            #+#    #+#             */
/*   Updated: 2023/04/19 16:42:03 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	parsing_handler(char *prompt)
{
	if (check_quote(prompt))
		return (1);
	if (check_pipe(prompt))
		return (1);
	if (check_redirecting(prompt))
	 	return (1);
	return (0);
}
