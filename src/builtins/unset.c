/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:09:26 by njegat            #+#    #+#             */
/*   Updated: 2023/05/03 18:13:30 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"
#include "../../include/utils.h"

static int	unset_parsing(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (1);
	if (isdigit(str[0]))
		return (1);
	while (isalnum(str[i]) || str[i] == '_')
		i++;
	if (!str[i])
		return (0);
	else
		return (1);
}

static int	unset_print_error(char *str)
{
	ft_putstr_fd("minishoul: unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static void	delete_var(t_data *data, char **env, char *arg)
{
	int	j;

	j = 0;
	while (env[j] != NULL)
	{
		if (var_is_equal(arg, env[j]) == TRUE)
		{
			data->env = str_delete(data->env, env[j]);
			break ;
		}
		j++;
	}
}

int	unset_builtins(t_data *data, char **arg)
{
	char	**tmp_env;
	int		i;
	int		error;

	error = 0;
	i = 1;
	while (arg[i])
	{
		tmp_env = data->env;
		if (!unset_parsing(arg[i]))
			delete_var(data, tmp_env, arg[i]);
		else
			error = unset_print_error(arg[i]);
		i++;
	}
	return (error);
}
