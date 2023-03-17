/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:26:13 by njegat            #+#    #+#             */
/*   Updated: 2023/03/17 16:07:22 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static void	error_quote(int s_quote, int d_quote)
{
	if (s_quote % 2)
		ft_putendl_fd("unclosed single quote", 2);
	if (d_quote % 2)
		ft_putendl_fd("unclosed double quote", 2);
}

int	check_quote(char *prompt)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (prompt[i])
	{
		if (prompt[i] == '"' && (s_quote % 2) == 0)
			d_quote++;
		if (prompt[i] == '\'' && (d_quote % 2) == 0)
			s_quote++;
		i++;
	}
	if (s_quote % 2 || d_quote % 2)
	{
		error_quote(s_quote, d_quote);
		return (1);
	}
	return (0);
}
