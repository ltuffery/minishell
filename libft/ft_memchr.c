/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:48:15 by njegat            #+#    #+#             */
/*   Updated: 2022/10/08 00:19:42 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*array;
	unsigned char	search;

	search = (unsigned char)c;
	array = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	while (*array != search && n - 1)
	{
		n--;
		array++;
	}
	if (*array == search)
		return (array);
	return (NULL);
}
