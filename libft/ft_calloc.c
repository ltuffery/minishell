/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 01:01:13 by njegat            #+#    #+#             */
/*   Updated: 2022/10/29 22:41:33 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	size_all;

	size_all = nmemb * size;
	if (!(nmemb || size))
	{
		array = malloc(0);
		return (array);
	}
	if ((size_all / nmemb) != size || (size_all / size) != nmemb)
		return (NULL);
	array = malloc(nmemb * size);
	if (!(array))
		return (NULL);
	ft_bzero(array, nmemb * size);
	return (array);
}
