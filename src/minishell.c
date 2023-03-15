/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:13:10 by njegat            #+#    #+#             */
/*   Updated: 2023/03/14 18:14:36 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	char	*promt;

	promt = NULL;
	if (argc != 1)
	{
		ft_putstr_fd("too many arguments", 2);
		return (0);
	}
	while (1)
	{
		if (promt)
		{
			free(promt);
			promt = NULL;
		}
		promt = readline("minishoul>");
		if (promt && *promt)
			add_history(promt);
	}
}
