/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:59:47 by njegat            #+#    #+#             */
/*   Updated: 2023/03/24 16:38:59 by njegat           ###   ########.fr       */
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

static int	is_quote(char *cmd, int pos)
{
	static int	s_quote;
	static int	d_quote;

	if (pos == -1)
		return ((s_quote + d_quote) % 2);
	if (cmd[pos] == '"' && (s_quote) == 0)
	{
		if (d_quote)
			d_quote = 0;
		else
			d_quote = 1;
		return (1);
	}
	else if (cmd[pos] == '\'' && (d_quote) == 0)
	{
		if (s_quote)
			s_quote = 0;
		else
			s_quote = 1;
		// if (cmd[pos + 1] == '$')
		// 	return (0);
		return (1);
	}
	return (0);
}

static void	add_unit(t_data *data, char *add, int *pos)
{
	int	i;

	i = *pos;
	add[i] = 0;
	i = 0;
	i = skip_set(add, " ");
	if (add[i])
		data->cmdx = ft_strappend(add, data->cmdx);
	*pos = 0;
}

void	get_cmd(t_data *data, char *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc((ft_strlen(cmd) + 1) * sizeof(char));
	i += skip_set(cmd + i, " ");
	while (cmd[i])
	{
		if (is_quote(cmd, i))
			i++;
		else if (is_chevron(cmd[i])  && !is_quote(NULL, -1))
			i = skip_redirect(cmd, i);
		else if (cmd[i] == ' ' && !is_quote(NULL, -1))
		{
			add_unit(data, tmp, &j);
			i += skip_set(cmd + i, " ");
		}
		else
			tmp[j++] = cmd[i++];
	}
	add_unit(data, tmp, &j);
	free(tmp);
}
