/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:59:47 by njegat            #+#    #+#             */
/*   Updated: 2023/03/30 18:57:03 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static int	skip_redirect(char *cmd, int pos)
{
	while (is_chevron(cmd[pos]))
		pos++;
	while (cmd[pos] == ' ')
		pos++;
	while (cmd[pos] != ' ' && cmd[pos])
		pos++;
	return (pos);
}

static void	add_unit(t_cmd *cmd, char *add, int *pos)
{
	int	i;

	i = *pos;
	add[i] = 0;
	i = 0;
	//i = skip_set(add, " ");
	if (add[i])
		cmd->arg = ft_strappend(add, cmd->arg);
	*pos = 0;
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
}

static int	insert_var(char *cmd, char *add, int *j, char **tmp)
{
	int	i;

	i = 0;
	if (cmd[i] == '$')
		i++;
	while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
		i++;
	if (!add)
		return (i);
	*tmp = ft_strjoin(*tmp, add);
	*j = ft_strlen(*tmp);
	free(add);
	return (i);
}

void	get_cmd(t_cmd *cmd, char *new_cmd, char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	*var;
	char	**split;

	i = 0;
	j = 0;
	tmp = malloc((ft_strlen(new_cmd) + 1) * sizeof(char));
	i += skip_set(new_cmd + i, " ");
	while (new_cmd[i])
	{
		if (is_quote(new_cmd[i], 0))
			i++;
		else if (is_chevron(new_cmd[i]) && !is_quote(0, 1))
			i = skip_redirect(new_cmd, i);
		else if (new_cmd[i] == ' ' && !is_quote(0, 1))
		{
			add_unit(cmd, tmp, &j);
			i += skip_set(new_cmd + i, " ");
		}
		else if (new_cmd[i] == '$' && is_quote(0, 1) != SIMPLE_QUOTE)
		{
			var = var_value(&new_cmd[i], env);
			tmp[j]= 0;
			if (is_quote(0, 1) == EMPTY_QUOTE && is_ambiguous(var))
			{
				split = ft_split(var, ' ');
				j = 0;
				add_units(cmd, split);
				i += var_len(&new_cmd[i]);
			}
			else
				i += insert_var(new_cmd + i, var, &j, &tmp);
		}
		else
			tmp[j++] = new_cmd[i++];
	}
	add_unit(cmd, tmp, &j);
	free(tmp);
}
