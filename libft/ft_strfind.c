/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:54:28 by njegat            #+#    #+#             */
/*   Updated: 2023/04/12 16:11:20 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strfind(const char *s, int c)
{
	int		i;
	char	search;

	if (s == NULL)
		return (0);
	search = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == search)
			return (i);
		i--;
	}
	return (0);
}
