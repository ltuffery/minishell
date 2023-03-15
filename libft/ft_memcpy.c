/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:27:34 by njegat            #+#    #+#             */
/*   Updated: 2022/10/16 04:23:44 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*array_src;
	unsigned char	*array_dest;
	size_t			i;

	if (!(dest || src))
		return (NULL);
	array_src = (unsigned char *)src;
	array_dest = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		array_dest[i] = array_src[i];
		i++;
	}
	return (dest);
}
