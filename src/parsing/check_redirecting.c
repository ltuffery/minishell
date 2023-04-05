/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:12:23 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/05 18:02:48 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/minishell.h"
#include <stddef.h>
#include <stdio.h>

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

static t_boolean	check_char(char c, t_boolean *rdct_find)
{
	static t_boolean	ret;
	static t_boolean	space_find;


	ret = FALSE;
	space_find = FALSE;
	if (c == '<' || c == '>')
	{
		if (space_find == TRUE && c == '>')
			ret = print_error(">");
		else if (space_find == TRUE && c == '<')
			ret = print_error("<");
		*rdct_find = TRUE;
	}
	else if (c == '|' && *rdct_find == TRUE)
		ret = print_error("|");
	else if (c != ' ' && c != '\t')
		*rdct_find = FALSE;
	else if (c == ' ' && c == '\t' && *rdct_find == TRUE)
		space_find = TRUE;
	return (ret);
}

int	check_redirecting(char *prompt)
{
	size_t		i;
	t_boolean	ret;
	t_boolean	rdct_find;

	i = 0;
	rdct_find = FALSE;
	while (prompt[i] != '\0')
	{
		ret = check_char(prompt[i], &rdct_find);
		if (ret != FALSE)
			break ;
		i++;
	}
	if (rdct_find == TRUE && ret == FALSE)
	{
		print_error("newline");
		return (1);
	}
	return (ret);
}
