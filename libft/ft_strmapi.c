/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 06:29:16 by njegat            #+#    #+#             */
/*   Updated: 2022/10/16 20:39:42 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*array;
	unsigned int	i;

	if (!(s) || !(f))
		return (NULL);
	i = 0;
	array = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!(array))
		return (NULL);
	while (i < ft_strlen(s))
	{
		array[i] = (*f)(i, s[i]);
		i++;
	}
	return (array);
}
