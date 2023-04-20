/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:59:47 by njegat            #+#    #+#             */
/*   Updated: 2023/04/20 16:20:14 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/utils.h"

static int	skip_redirect(char *cmd, int pos)
{
	while (is_chevron(cmd[pos]))
		pos++;
	while (cmd[pos] == ' ')
		pos++;
	while (cmd[pos] != ' ' && cmd[pos])
		pos++;
	while (cmd[pos] == ' ')
		pos++;
	return (pos);
}

static void	add_units(t_cmd *cmd, char **adds)
{
	int	i;

	i = 0;
	while (adds[i] != NULL)
	{
		cmd->arg = ft_strappend(adds[i], cmd->arg);
		i++;
	}
	ft_double_free(adds);
}

static int	insert_var(char *cmd, char *add, char **tmp)
{
	int	i;

	i = var_len(cmd);
	if (!add)
		return (i);
	if (!*tmp)
	{
		*tmp = malloc(1);
		*tmp[0] = 0;
	}
	*tmp = ft_strjoin(*tmp, add);
	return (i);
}

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

	if (!str)
	{
		out = malloc(sizeof(char) * 2);
		out[0] = c;
		out[1] = 0;
		return (out);
	}
	else
		out = malloc(sizeof(char) * ft_strlen(str) + 3);
	if (!out)
		return (NULL);
	ft_strlcpy(out, str, ft_strlen(str) + 1);
	i = 0;
	while (out[i])
		i++;
	out[i] = c;
	out[i + 1] = 0;
	free(str);
	return (out);
}

int	get_replace_var(t_cmd *cmd, char *new_cmd, char **env, char **tmp)
{
	char	*var;
	char	**split;
	int		skip;

	skip = 0;
	var = var_value(new_cmd, env);
	if (is_quote(0, 1) == EMPTY_QUOTE && is_ambiguous(var))
	{
		split = ft_split(var, ' ');
		free (*tmp);
		*tmp = NULL;
		add_units(cmd, split);
		skip = var_len(new_cmd);
	}
	else
	{
		skip = insert_var(new_cmd, var, tmp);
		if (is_quote(0, 1) == EMPTY_QUOTE && !var)
			skip += skip_set(new_cmd + skip, " ");
	}
	free(var);
	return (skip);
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
		else if (line[i] == ' ' && !is_quote(0, 1))
		{
			add_unit(cmd, &buffer);
			i += skip_set(line + i, " \t");
		}
		else if (line[i] == '$' && is_quote(0, 1) != SIMPLE_QUOTE)
			i += get_replace_var(cmd, line + i, env, &buffer);
		else
			buffer = add_c(buffer, line[i++]);
	}
	if (buffer != NULL)
		add_unit(cmd, &buffer);
	free(buffer);
}
