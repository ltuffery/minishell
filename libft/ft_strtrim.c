/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 03:05:05 by njegat            #+#    #+#             */
/*   Updated: 2023/01/24 06:10:16 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charset(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static size_t	ft_set_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (ft_charset(s1[i], set))
		i++;
	return (i);
}

static size_t	ft_set_end(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (ft_charset(s1[i], set))
		i--;
	return (i);
}

static char	*ft_alloc(char const *s, size_t start, size_t end)
{
	char	*array;

	if (start == ft_strlen(s))
	{
		array = ft_calloc(1, sizeof(char));
		return (array);
	}
	array = ft_calloc((end - (start - 1)) + 1, sizeof(char));
	return (array);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*array;
	size_t		start;
	size_t		end;
	int			i;

	if (!(s1) || !(set))
		return (NULL);
	i = 0;
	start = ft_set_start(s1, set);
	end = ft_set_end(s1, set);
	array = ft_alloc(s1, start, end);
	if (array == NULL)
		return (NULL);
	if (start == ft_strlen(s1))
		return (array);
	while (start <= end)
	{
		array[i] = s1[start];
		i++;
		start++;
	}
	return (array);
}
