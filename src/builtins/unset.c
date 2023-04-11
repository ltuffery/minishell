/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:09:26 by njegat            #+#    #+#             */
/*   Updated: 2023/04/11 15:21:24 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"
#include "../../include/utils.h"

static int	unset_parsing(char *str)
{
	int	i;

	i = 0;
	if (isdigit(str[0]))
		return (1);
	while (isalnum(str[i]) || str[i] == '_')
		i++;
	if (!str[i])
		return (0);
	else
		return (1);
}

static void	unset_print_error(char *str)
{
	ft_putstr_fd("minishoul: unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	unset_builtins(t_data *data, char **arg)
{
	char	**tmp_env;
	int		i;
	int		j;

	i = 1;
	while (arg[i])
	{
		j = 0;
		tmp_env = data->env;
		if (!unset_parsing(arg[i]))
		{
			while (tmp_env[j])
			{
				if (var_is_equal(arg[i], tmp_env[j]) == TRUE)
					data->env = str_delete(data->env, tmp_env[j]);
				j++;
			}
		}
		else
			unset_print_error(arg[i]);
		i++;
	}
}
