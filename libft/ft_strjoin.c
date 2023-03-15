/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 02:28:00 by njegat            #+#    #+#             */
/*   Updated: 2023/01/04 09:13:19 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy_pos(char *s1, const char *s2, int pos)
{
	unsigned int	i;

	i = 0;
	while (s2[i])
	{
		s1[pos] = s2[i];
		pos++;
		i++;
	}
	s1[pos] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*array;

	if (!(s1) || !(s2))
		return (NULL);
	array = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!(array))
	{
		free(s1);
		return (NULL);
	}
	ft_strcpy_pos(array, s1, 0);
	ft_strcpy_pos(array, s2, ft_strlen(s1));
	free(s1);
	return (array);
}
