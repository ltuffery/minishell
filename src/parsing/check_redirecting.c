/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:12:23 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/28 20:01:29 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stddef.h>
#include <stdio.h>

static void	print_error(char token)
{
	char	*msg;

	msg = ft_strdup("minishoul: syntax error near unexpected token ");
	msg = ft_strjoin(msg, &token);
	if (msg == NULL)
		return ;
	ft_putendl_fd(msg, 2);
}

int	check_redirecting(char *prompt)
{
	char	token;
	int		is_use;
	size_t	i;

	i = 0;
	while (prompt[i] != '\0')
	{
		if (prompt[i] == '<' || prompt[i] == '>')
		{
			token = prompt[i];
			is_use = 0;
		}
		else if (ft_isprint(prompt[i]) && prompt[i] != ' ')
			is_use = 1;
		i++;
	}
	if (is_use == 0)
	{
		print_error(token);
		return (1);
	}
	return (0);
}
