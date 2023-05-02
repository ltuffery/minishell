/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:06:35 by ltuffery          #+#    #+#             */
/*   Updated: 2023/05/02 15:59:48 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/utils.h"
#include "../../libft/libft.h"
#include <stdio.h>

static int	check_is_superior_max(char *code, int is_neg)
{
	if (code[0] <= '9' && \
			code[1] <= '2' && \
			code[2] <= '2' && \
			code[3] <= '3' && \
			code[4] <= '3' && \
			code[5] <= '7' && \
			code[6] <= '2' && \
			code[7] <= '0' && \
			code[8] <= '3' && \
			code[9] <= '6' && \
			code[10] <= '8' && \
			code[11] <= '5' && \
			code[12] <= '4' && \
			code[13] <= '7' && \
			code[14] <= '7' && \
			code[15] <= '5' && \
			code[16] <= '8' && \
			code[17] <= '0')
	{
		if ((is_neg && code[18] <= '8') || (!is_neg && code[18] <= '7'))
			return (0);
	}
	return (1);
}

static void	change_code(char *code)
{
	long long	status;

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
	if (args[1][0] == '-' && ft_isdigit(args[1][1]))
		i++;
	if (args[1] != NULL)
	{
		if (ft_strlen(args[1]) > 19)
			return (1);
		else if (check_is_superior_max(&args[1][i], i))
			return (1);
		change_code(&args[1][i]);
		while (args[1][i] != '\0')
		{
			if (!ft_isdigit(args[1][i]))
				return (1);
			i++;
		}
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
