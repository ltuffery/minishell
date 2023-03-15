/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:27:15 by njegat            #+#    #+#             */
/*   Updated: 2023/01/31 03:14:32 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_convert(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	return (-1);
}

int	ft_atoi_base(char *s, int base)
{
	int	value;
	int	sign;
	int	digit;

	value = 0;
	sign = 1;
	digit = 0;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while (*s)
	{
		if (ft_convert(*s) != -1)
			digit = ft_convert(*s);
		else
			break ;
		if (digit >= base)
			break ;
		value = value * base + digit;
		s++;
	}
	return (value * sign);
}
