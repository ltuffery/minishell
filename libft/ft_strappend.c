/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:55:56 by ltuffery          #+#    #+#             */
/*   Updated: 2022/11/28 13:45:46 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strappend(char *add, char **in)
{
	char	**new_tab;
	int		i;

	if (in == NULL)
	{
		new_tab = ft_calloc(2, sizeof(char *));
		new_tab[0] = ft_strdup(add);
		return (new_tab);
	}
	i = 0;
	while (in[i] != NULL)
		i++;
	new_tab = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (in[i] != NULL)
	{
		new_tab[i] = in[i];
		i++;
	}
	new_tab[i] = ft_strdup(add);
	new_tab[i + 1] = NULL;
	free(in);
	return (new_tab);
}
