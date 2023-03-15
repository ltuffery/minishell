/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 06:07:22 by njegat            #+#    #+#             */
/*   Updated: 2022/10/29 19:15:45 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_word(const char *array, char c)
{
	int	count;

	count = 0;
	while (*array)
	{
		while (*array == c)
			array++;
		if (*array != c && *array)
		{
			while (*array != c && *array)
				array++;
			count++;
		}
	}
	return (count);
}

static void	ft_free_all(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	ft_alloc_write(char **array_final, const char *array, char c)
{
	int		i;
	int		j;

	j = 0;
	while (*array)
	{
		while (*array == c)
			array++;
		i = 0;
		if (*array)
		{
			while (array[i] != c && array[i])
				i++;
			array_final[j] = ft_substr(array, 0, i);
			if (!(array_final[j]))
			{
				ft_free_all(array_final);
				return ;
			}
			array += i;
			j++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**array_final;

	if (!(s))
		return (NULL);
	array_final = ft_calloc(ft_nb_word(s, c) + 1, sizeof(char *));
	if (!(array_final))
		return (NULL);
	ft_alloc_write(array_final, s, c);
	if (!(array_final))
		return (NULL);
	return (array_final);
}
