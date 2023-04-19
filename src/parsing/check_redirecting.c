/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:12:23 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/19 17:55:54 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/minishell.h"
#include "../../include/utils.h"
#include <stdlib.h>

static t_boolean	print_error(char *error)
{
	char	*msg;

	msg = ft_strdup("minishoul: syntax error near unexpected token '");
	msg = ft_strjoin(msg, error);
	msg = ft_strjoin(msg, "'");
	if (msg == NULL)
		return (TRUE);
	ft_putendl_fd(msg, 2);
	free(msg);
	return (TRUE);
}

static t_boolean	chevron_manager(char c, char lc, t_boolean reset)
{
	static char	token;
	static int	token_find;
	t_boolean	ret;

	ret = FALSE;
	if (token == '\0')
		token = c;
	token_find++;
	if ((!is_chevron(c) && c != '|') || reset)
	{
		token = '\0';
		token_find = 0;
		return (ret);
	}
	if (token_find > 2)
		ret = print_error("<<< or >>>");
	else if (c == '|')
		ret = print_error("|");
	else if (c != token)
		ret = print_error("< or >");
	else if (lc == '\0')
		ret = print_error("newline");
	return (ret);
}

int	check_redirecting(char *prompt)
{
	size_t		i;
	t_boolean	ret;

	i = 0;
	while (prompt[i] != '\0')
	{
		if (prompt[i + 1] != '\0')
			ret = chevron_manager(prompt[i], prompt[i + 1], FALSE);
		if (ret)
			break ;
		i++;
	}
	chevron_manager('\0', '\0', TRUE);
	return (ret);
}
