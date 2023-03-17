/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:41:24 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/17 15:27:06 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishel.h"

void	echo_builtins(const int argc, const char **argv, const t_boolean flag)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i != argc - 1)
			printf(" ");
		i++;
	}
	if (flag == FALSE)
		printf("\n");
}
