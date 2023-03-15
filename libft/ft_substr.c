/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 02:10:18 by njegat            #+#    #+#             */
/*   Updated: 2022/10/15 23:21:56 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*array;
	unsigned int	i;

	if (!(s))
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
	{
		array = ft_calloc(1, sizeof(char));
		return (array);
	}
	else if (len >= (ft_strlen(s) - start))
		array = ft_calloc((ft_strlen(s) - start) + 1, sizeof(char));
	else
		array = ft_calloc((len) + 1, sizeof(char));
	if (!(array))
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		array[i] = s[start];
		i++;
		start++;
	}
	return (array);
}
