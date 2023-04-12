/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:54:28 by njegat            #+#    #+#             */
/*   Updated: 2023/04/11 15:02:35 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strfind(const char *s, int c)
{
	int		i;
	char	search;

	if (s == NULL)
		return (-1);
	search = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == search)
			return (i);
		i--;
	}
	return (-1);
}
