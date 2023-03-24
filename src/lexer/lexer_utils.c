/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:22:52 by njegat            #+#    #+#             */
/*   Updated: 2023/03/24 17:23:19 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	is_chevron(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	skip_set(char *str, char *set)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				count++;
			j++;
		}
		if (count == i)
			break ;
		else
			i++;
	}
	return (count);
}

int	is_quote(char str, int get)
{
	static int	s_quote;
	static int	d_quote;

	if (get == 1)
		return ((s_quote + d_quote) % 2);
	if (str == '"' && s_quote == 0)
	{
		d_quote = !d_quote;
		return (1);
	}
	else if (str == '\'' && d_quote == 0)
	{
		s_quote = !s_quote;
		return (1);
	}
	return (0);
}

