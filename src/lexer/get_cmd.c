/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:59:47 by njegat            #+#    #+#             */
/*   Updated: 2023/05/03 15:03:02 by njegat           ###   ########.fr       */
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

static int	quotes(t_cmd *cmd, char *line, int *i, char **buffer)
{
	if (is_quote(line[*i], 0))
	{
		(*i)++;
		if (line[*i] == '\0')
			add_unit(cmd, buffer);
		return (1);
	}
	return (0);
}

void	tokens_manager(t_cmd *cmd, char *line, char **env)
{
	char	*buffer;
	int		i;

	i = skip_set(line, " \t");
	buffer = NULL;
	while (line[i] != '\0')
	{
		if (quotes(cmd, line, &i, &buffer))
			continue ;
		if (is_chevron(line[i]) && !is_quote(0, 1))
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
