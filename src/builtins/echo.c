/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:41:24 by ltuffery          #+#    #+#             */
/*   Updated: 2023/05/07 17:30:22 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_boolean	is_flag(const char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (FALSE);
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	skip_flags(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (!is_flag(argv[i]))
			break ;
		i++;
	}
	return (i - 1);
}

int	echo_builtins(char **argv)
{
	int			i;
	t_boolean	has_flag;

	i = 1;
	has_flag = FALSE;
	i += skip_flags(argv);
	if (i > 1)
		has_flag = TRUE;
	if (argv[1] != NULL)
	{
		while (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			if (argv[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	if (has_flag == FALSE)
		printf("\n");
	return (0);
}
