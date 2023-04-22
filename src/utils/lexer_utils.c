/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:22:52 by njegat            #+#    #+#             */
/*   Updated: 2023/04/22 19:47:43 by njegat           ###   ########.fr       */
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
	if (!str)
		return (0);
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
	{
		if (s_quote)
			return (SIMPLE_QUOTE);
		else if (d_quote)
			return (DOOBLE_QUOTE);
		return (0);
	}
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

int	skip_redirect(char *cmd, int pos)
{
	int	quotes;

	quotes = is_quote(0, 1);
	while (is_chevron(cmd[pos]))
		pos++;
	while (cmd[pos] == ' ')
		pos++;
	while ((cmd[pos] != ' ' || quotes) && cmd[pos])
	{
		if (cmd[pos] == '\'' || cmd[pos] == '"')
			quotes = !quotes;
		pos++;
	}
	while (cmd[pos] == ' ')
		pos++;
	return (pos);
}
