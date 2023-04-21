/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:59:47 by njegat            #+#    #+#             */
/*   Updated: 2023/04/21 18:54:20 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/utils.h"

static void	add_unit(t_cmd *cmd, char **add)
{
	cmd->arg = ft_strappend(*add, cmd->arg);
	free (*add);
	*add = NULL;
}

char	*add_c(char *str, char c)
{
	char	*out;
	int		i;

	i = 0;
	out = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	if (out == NULL)
		return (NULL);
	if (str != NULL)
	{
		ft_strlcpy(out, str, ft_strlen(str) + 1);
		free(str);
	}
	while (out[i])
		i++;
	out[i] = c;
	out[i + 1] = '\0';
	return (out);
}

void	tokens_manager(t_cmd *cmd, char *line, char **env)
{
	char	*buffer;
	int		i;

	i = skip_set(line, " \t");
	buffer = NULL;
	while (line[i] != '\0')
	{
		if (is_quote(line[i], 0))
			i++;
		else if (is_chevron(line[i]) && !is_quote(0, 1))
			i = skip_redirect(line, i);
		else if ((line[i] == ' ' || line[i] == '\t') && !is_quote(0, 1))
		{
			add_unit(cmd, &buffer);
			i += skip_set(line + i, " \t");
		}
		else if (line[i] == '$' && is_quote(0, 1) != SIMPLE_QUOTE)
			i += variable(cmd, line + i, env, &buffer);
		else
			buffer = add_c(buffer, line[i++]);
	}
	if (buffer != NULL)
		add_unit(cmd, &buffer);
	free(buffer);
}
