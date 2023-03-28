/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:26:58 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 18:32:06 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../../include/builtins.h"
#include "../../../include/utils.h"

static void	printw_quote(char **env, char *line)
{
	char	*var;
	char	*tmp;

	var = getvar(line);
	if (!var)
		return ;
	tmp = getvalue(env, var);
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(var, 1);
	if (line[ft_strlen(var)] == '=')
	{
		if (tmp)
			printf("=\"%s\"\n", tmp);
		else
			printf("=\"\"\n");
	}
	else
		printf("\n");
	free(var);
	free(tmp);
}

void	print_by_order(char **env)
{
	int		i;
	char	*tmp;
	char	**old_env;

	while (env)
	{
		i = 0;
		tmp = NULL;
		while (env[i])
		{
			if (!tmp)
				tmp = env[i];
			if (ft_strcmp(env[i], tmp) < 0)
			{
				tmp = env[i];
				i = 0;
				continue ;
			}
			i++;
		}
		if (tmp)
			printw_quote(env, tmp);
		old_env = env;
		env = str_delete(env, tmp);
	}
	ft_double_free(old_env);
}
