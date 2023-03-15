/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:01:40 by njegat            #+#    #+#             */
/*   Updated: 2022/10/08 00:20:38 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*array;
	int		i;
	char	search;

	array = (char *)s;
	search = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == search)
			return (array + i);
		i++;
	}
	if (s[i] == search)
		return (array + i);
	return (NULL);
}
