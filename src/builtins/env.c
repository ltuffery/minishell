/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:36:37 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/27 16:03:32 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stdio.h>

int	env_builtins(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strfind(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
