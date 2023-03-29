/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:12:23 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/29 17:14:29 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stddef.h>
#include <stdio.h>

static void	print_error(char token)
{
	char	*msg;
	size_t	msg_len;

	msg = ft_strdup("minishoul: syntax error near unexpected token ' ");
	msg_len = ft_strlen(msg);
	msg[msg_len - 1] = token;
	msg = ft_strjoin(msg, "'");
	if (msg == NULL)
		return ;
	ft_putendl_fd(msg, 2);
	free(msg);
}

static int	check(int status, char token, char prompt)
{
	if (status == 2)
	{
		print_error(token);
		return (1);
	}
	else if (status == 1 && prompt != token)
	{
		print_error(token);
		return (1);
	}
	return (0);
}

int	check_redirecting(char *prompt)
{
	char	token;
	size_t	i;
	int		status;

	i = 0;
	status = 0;
	token = '\0';
	while (prompt[i] != '\0')
	{
		if (prompt[i] == '>' || prompt[i] == '<' || prompt[i] == '|')
		{
			if (check(status, token, prompt[i]))
				return (1);
			token = prompt[i];
			status++;
		}
		else if (prompt[i] != ' ')
		{
			token = '\0';
			status = 0;
		}
		i++;
	}
	return (0);
}
