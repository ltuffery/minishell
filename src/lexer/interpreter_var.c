/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:22:38 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/28 18:03:33 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*var_value(char *line)
{
	size_t	i;
	char	*ret;
	char	*value;

	i = 0;
	if (line[i] == '$')
		i++;
	ret = ft_strdup(&line[i]);
	i = 0;
	if (ret == NULL)
		return (NULL);
	while (ft_isalnum(ret[i]) || ret[i] == '_')
		i++;
	ret[i] = '\0';
	if (ft_isdigit(ret[0]))
		value = ft_strdup(&ret[1]);
	else
		value = getenv(ret);
	free(ret);
	if (value == NULL)
		return (NULL);
	return (value);
}
