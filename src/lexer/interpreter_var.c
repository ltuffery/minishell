/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:22:38 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/27 13:10:52 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stdlib.h>

char	*var_value(char *line)
{
	char	*var;
	char	*ret;
	char	*value;

	var = ft_strtrim(line, "\"' ");
	ret = ft_strchr(var, '$');
	if (ret == NULL)
		return (NULL);
	value = getenv(&ret[1]);
	free(var);
	if (value == NULL)
		return (line);
	return (value);
}
