/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 23:29:03 by njegat            #+#    #+#             */
/*   Updated: 2022/10/16 04:23:13 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*array1;
	unsigned char	*array2;

	array1 = (unsigned char *)s1;
	array2 = (unsigned char *)s2;
	while (n)
	{
		n--;
		if (*array1 != *array2)
		{
			return (*array1 - *array2);
		}
		array1++;
		array2++;
	}
	return (0);
}
