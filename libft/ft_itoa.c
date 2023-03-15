/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 04:00:30 by njegat            #+#    #+#             */
/*   Updated: 2022/10/29 22:25:43 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long nb)
{
	int	i;

	i = 0;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*array;
	int		isnegative;
	long	nb;

	isnegative = 0;
	nb = (long)n;
	if (nb < 0)
		isnegative = 1;
	if (nb < 0)
		nb *= -1;
	i = ft_intlen(nb);
	array = ft_calloc((i + isnegative) + 1, sizeof(char));
	if (!(array))
		return (NULL);
	while (i > 0)
	{
		array[(i - 1) + isnegative] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	if (isnegative)
		array[0] = '-';
	return (array);
}
