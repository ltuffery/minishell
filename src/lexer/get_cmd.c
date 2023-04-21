/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:59:47 by njegat            #+#    #+#             */
/*   Updated: 2023/04/21 16:54:09 by njegat           ###   ########.fr       */
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

	if (str == NULL)
	{
		out = malloc(sizeof(char) * 2);
		out[0] = c;
		out[1] = '\0';
		return (out);
	}
	else
		out = malloc(sizeof(char) * ft_strlen(str) + 3);
	if (out == NULL)
		return (NULL);
	ft_strlcpy(out, str, ft_strlen(str) + 1);
	i = 0;
	while (out[i])
		i++;
	out[i] = c;
	out[i + 1] = '\0';
	free(str);
	return (out);
}

void	tokens_manager(t_cmd *cmd, char *line, char **env)
{
	char	*buffer;
	int		i;

	(void)env;
	if (!line)
		return ;
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
