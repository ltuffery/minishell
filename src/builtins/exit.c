/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:06:35 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/27 16:04:32 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/utils.h"
#include "../../libft/libft.h"
#include <stdio.h>

static void	change_code(char *code)
{
	unsigned long long	status;

	status = ft_atoll(code);
	set_code(status % 256, FALSE);
}

static int	check_args(char **args)
{
	size_t	i;

	i = 0;
	if (args[1] == NULL)
		return (0);
	if (args[2] != NULL)
		return (-1);
	if (args[1] != NULL)
	{
		while (args[1][i] != '\0')
		{
			if (!ft_isdigit(args[1][i]))
				return (1);
			i++;
		}
		change_code(args[1]);
	}
	return (0);
}

void	exit_builtins(t_data *data, char **args)
{
	int	code;
	int	check;

	check = check_args(args);
	ft_putendl_fd("exit", 1);
	if (check == -1)
	{
		set_code(1, FALSE);
		ft_putendl_fd("minishoul: exit: too many arguments", 2);
		return ;
	}
	else if (check == 1)
	{
		ft_putstr_fd("minishoul: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		set_code(2, FALSE);
	}
	free_struct(&data->cmd);
	ft_double_free(data->env);
	code = exitcode()->code;
	free(exitcode());
	exit(code);
}
