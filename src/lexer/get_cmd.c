/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:59:47 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 19:51:15 by njegat           ###   ########.fr       */
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

static void	add_unit(t_data *data, char *add, int *pos)
{
	int	i;

	i = *pos;
	add[i] = 0;
	i = 0;
	//i = skip_set(add, " ");
	if (add[i])
		data->cmdx = ft_strappend(add, data->cmdx);
	*pos = 0;
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

void	get_cmd(t_data *data, char *cmd, t_env *my_env)
{
	int		i;
	int		j;
	char	*tmp;
	char	*var;

	i = 0;
	j = 0;
	tmp = malloc((ft_strlen(cmd) + 1) * sizeof(char));
	i += skip_set(cmd + i, " ");
	while (cmd[i])
	{
		if (is_quote(cmd[i], 0))
			i++;
		else if (is_chevron(cmd[i]) && !is_quote(0, 1))
			i = skip_redirect(cmd, i);
		else if (cmd[i] == ' ' && !is_quote(0, 1))
		{
			add_unit(data, tmp, &j);
			i += skip_set(cmd + i, " ");
		}
		else if (cmd[i] == '$' && is_quote(0, 1) != SIMPLE_QUOTE)
		{
			var = var_value(&cmd[i], my_env);
			tmp[j]= 0;
			i += insert_var(cmd + i, var, &j, &tmp);
		}
		else
			tmp[j++] = cmd[i++];
	}
	add_unit(data, tmp, &j);
	free(tmp);
}
