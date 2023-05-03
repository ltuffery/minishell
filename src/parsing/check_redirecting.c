/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:12:23 by ltuffery          #+#    #+#             */
/*   Updated: 2023/05/03 16:24:30 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/minishell.h"
#include "../../include/utils.h"
#include <stdlib.h>

static t_boolean	print_error(char *error)
{
	ft_putstr_fd("minishoul: syntax error near unexpected token '", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("'", 2);
	return (TRUE);
}

static int	chevron_manager(char *prompt, t_boolean *error)
{
	int		i;
	char	str[2];

	i = 1;
	if (prompt[i] == '<' || prompt[i] == '>')
		i++;
	i += skip_set(prompt + i, " \t");
	str[0] = prompt[i];
	str[1] = 0;
	if (prompt[0] == '<' && prompt[1] == '>')
		*error = print_error(">");
	else if (prompt[0] == '>' && prompt[1] == '<')
		*error = print_error("<");
	else if (prompt[i] == '<' || prompt[i] == '>' || prompt[i] == '|')
		*error = print_error(str);
	else if (!prompt[i])
		*error = print_error("newline");
	return (i);
}

int	check_redirecting(char *prompt)
{
	int			i;
	t_boolean	error;
	t_boolean	d_quote;
	t_boolean	s_quote;

	error = FALSE;
	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' && !(d_quote % 2))
			s_quote++;
		if (prompt[i] == '"' && !(s_quote % 2))
			d_quote++;
		if ((prompt[i] == '>' || prompt[i] == '<') && \
				s_quote % 2 == 0 && d_quote % 2 == 0)
			i += chevron_manager(prompt + i, &error);
		if (error == TRUE)
			return (error);
		i++;
	}
	return (error);
}
