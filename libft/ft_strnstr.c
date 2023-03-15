/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:20:58 by njegat            #+#    #+#             */
/*   Updated: 2022/10/29 21:38:36 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_equal(char *s1, const char *s2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && s2[i])
	{
		if (s1[i] != s2[i] || s1[i] == '\0')
			return (1);
		i++;
	}
	if (s2[i] != '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	char	*output;

	i = 0;
	output = (char *)big;
	if (!(big || len))
		return (NULL);
	if (*little == '\0')
		return (output);
	while (big[i] && (len - i))
	{
		if (big[i] == little[0])
		{
			if (!(ft_is_equal(output + i, little, len - i)))
				return (output + i);
		}
		i++;
	}
	return (NULL);
}
