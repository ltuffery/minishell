/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:22:38 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/29 18:16:26 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/utils.h"

char	*var_value(char *line, char **env)
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
		value = getvalue(env, ret);
	free(ret);
	if (value == NULL)
		return (NULL);
	return (value);
}
