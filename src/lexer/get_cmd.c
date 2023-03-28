/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:59:47 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 13:32:51 by ltuffery         ###   ########.fr       */
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
		if (is_quote(cmd[i], 0))
			i++;
		else if (is_chevron(cmd[i]) && !is_quote(0, 1))
			i = skip_redirect(cmd, i);
		else if (cmd[i] == ' ' && !is_quote(0, 1))
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
