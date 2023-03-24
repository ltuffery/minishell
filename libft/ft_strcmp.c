/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:29:16 by njegat            #+#    #+#             */
/*   Updated: 2023/03/22 17:42:44 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (1);
	// if (ft_strlen(str1) < ft_strlen(str2))
	// 	return (ft_strlen(str1) - ft_strlen(str2));
	i = 0;
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
