/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:12:23 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/21 18:41:00 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/minishell.h"
#include "../../include/utils.h"
#include <stdlib.h>

// static t_boolean	print_error(char *error)
// {
// 	char	*msg;

// 	msg = ft_strdup("minishoul: syntax error near unexpected token '");
// 	msg = ft_strjoin(msg, error);
// 	msg = ft_strjoin(msg, "'");
// 	if (msg == NULL)
// 		return (TRUE);
// 	ft_putendl_fd(msg, 2);
// 	free(msg);
// 	return (TRUE);
// }

// static t_boolean	chevron_manager(char c, char lc, t_boolean reset)
// {
// 	static char	token;
// 	static int	token_find;
// 	t_boolean	ret;

// 	ret = FALSE;
// 	if (token == '\0')
// 		token = c;
// 	token_find++;
// 	if ((!is_chevron(c) && c != '|') || reset)
// 	{
// 		token = '\0';
// 		token_find = 0;
// 		return (ret);
// 	}
// 	if (token_find > 2)
// 		ret = print_error("<<< or >>>");
// 	else if (c == '|')
// 		ret = print_error("|");
// 	else if (c != token)
// 		ret = print_error("< or >");
// 	else if (lc == '\0')
// 		ret = print_error("newline");
// 	return (ret);
// }

// int	check_redirecting(char *prompt)
// {
// 	size_t		i;
// 	t_boolean	ret;

// 	i = 0;
// 	while (prompt[i] != '\0')
// 	{
// 		if (prompt[i + 1] != '\0')
// 			ret = chevron_manager(prompt[i], prompt[i + 1], FALSE);
// 		if (ret)
// 			break ;
// 		i++;
// 	}
// 	chevron_manager('\0', '\0', TRUE);
// 	return (ret);
// }

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
	if (prompt[i] == '<' || prompt[i] == '>' || prompt[i] == '|')
		*error = print_error(str);
	else if (!prompt[i])
		*error = print_error("newline");
	if (prompt[0] == '<' && prompt[1] == '>')
		*error = print_error(">");
	else if (prompt[0] == '>' && prompt[1] == '<')
		*error = print_error("<");
	return (i);
}

int	check_redirecting(char *prompt)
{
	int			i;
	t_boolean	error;

	error = FALSE;
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '>' || prompt[i] == '<')
			i += chevron_manager(prompt + i, &error);
		if (error == TRUE)
			return (error);
		i++;
	}
	return (error);
}
