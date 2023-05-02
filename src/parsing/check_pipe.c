/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:05:34 by njegat            #+#    #+#             */
/*   Updated: 2023/05/02 16:19:18 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/utils.h"

static int	check_nb_pipe(char *prompt)
{
	int	i;
	int	pipe;
	int	s_quote;
	int	d_quote;

	i = 0;
	pipe = 0;
	s_quote = 0;
	d_quote = 0;
	while (prompt[i])
	{
		i += skip_set(prompt + i, " \t");
		if (prompt[i] == '"' && (s_quote % 2) == 0)
			d_quote++;
		if (prompt[i] == '\'' && (d_quote % 2) == 0)
			s_quote++;
		if (prompt[i] == '|' && !(d_quote % 2) && !(s_quote % 2))
			pipe++;
		if (prompt[i] != '|' && pipe > 1)
			return (pipe);
		if (prompt[i] != '|')
			pipe = 0;
		i++;
	}
	return (pipe);
}

static int	around_pipe(char *prompt)
{
	char	*tmp;

	tmp = ft_strtrim(prompt, " \t");
	if (!tmp)
		return (0);
	if (!tmp[0])
	{
		free(tmp);
		return (0);
	}
	if (tmp[0] == '|' || tmp[ft_strlen(tmp) - 1] == '|')
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	check_pipe(char *prompt)
{
	if (check_nb_pipe(prompt) > 1)
	{
		ft_putendl_fd("syntax error near unexpected token '|'", 2);
		return (1);
	}
	if (around_pipe(prompt))
	{
		ft_putendl_fd("syntax error near unexpected token '|'", 2);
		return (1);
	}
	return (0);
}
