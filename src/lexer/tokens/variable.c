/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:26:39 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/21 18:13:02 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/lexer.h"
#include "../../../include/utils.h"

static void	add_units(t_cmd *cmd, char **adds, char **tmp)
{
	int	i;

	i = 0;
	while (adds[i] != NULL)
	{
		if (adds[i + 1] != NULL)
			cmd->arg = ft_strappend(adds[i], cmd->arg);
		i++;
	}
	*tmp = ft_strdup(adds[i - 1]);
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

int	variable(t_cmd *cmd, char *line, char **env, char **tmp)
{
	char	*var;
	char	*tmp_split;
	char	**split;
	int		skip;

	skip = 0;
	var = var_value(line, env);
	if (is_quote(0, 1) == EMPTY_QUOTE && is_ambiguous(var))
	{
		split = ft_split(var, ' ');
		tmp_split = split[0];
		if (*tmp && split[0])
		{
			split[0] = ft_strjoin(*tmp, split[0]);
			free(tmp_split);
		}
		*tmp = NULL;
		add_units(cmd, split, tmp);
		skip = var_len(line);
	}
	else
	{
		skip = insert_var(line, var, tmp);
		if (is_quote(0, 1) == EMPTY_QUOTE && var == NULL)
			skip += skip_set(line + skip, " ");
	}
	free(var);
	return (skip);
}
