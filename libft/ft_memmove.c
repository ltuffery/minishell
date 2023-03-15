/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:33:43 by njegat            #+#    #+#             */
/*   Updated: 2022/10/16 04:27:20 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*array_src;
	unsigned char	*array_dest;

	if (!(dest || src))
		return (NULL);
	array_src = (unsigned char *)src;
	array_dest = (unsigned char *)dest;
	if (dest < src)
	{
		ft_memcpy(dest, src, n);
		return (dest);
	}
	while (n)
	{
		n--;
		array_dest[n] = array_src[n];
	}
	return (dest);
}
