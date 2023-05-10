/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:06:35 by ltuffery          #+#    #+#             */
/*   Updated: 2023/05/10 15:59:17 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/utils.h"
#include "../../libft/libft.h"
#include <stdio.h>

static int	check_max(char *code, int is_neg)
{
	char		*limit;
	int			i;
	t_boolean	has_diff;

	i = 0;
	has_diff = FALSE;
	if (is_neg)
		limit = ft_strdup("-9223372036854775808");
	else
		limit = ft_strdup("9223372036854775807");
	while (code[i] != '\0')
	{
		if (code[i] < limit[i])
			has_diff = TRUE;
		else if (code[i] > limit[i] && has_diff == FALSE)
		{
			free(limit);
			return (1);
		}
		i++;
	}
	free(limit);
	return (0);
}

static void	change_code(char *code)
{
	long long	status;

	status = ft_atoll(code);
	set_code(status % 256, FALSE);
}

static int	check_has_alpha(char *code)
{
	int	i;

	i = 0;
	while (code[i] != '\0')
	{
		if (!ft_isdigit(code[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	check_args(char **args)
{
	size_t	i;

	i = 0;
	if (args[1] == NULL)
		return (0);
	if (args[1][0] == '-' && ft_isdigit(args[1][1]))
		i++;
	if (args[1] != NULL)
	{
		if (ft_strlen(args[1]) > 19 + i)
			return (1);
		else if (ft_strlen(args[1]) == 19 + i)
		{
			if (check_max(args[1], i))
				return (1);
		}
		change_code(args[1]);
		if (check_has_alpha(&args[1][i]))
			return (1);
	}
	if (args[2] != NULL)
		return (-1);
	return (0);
}

int	exit_builtins(t_data *data, char **args)
{
	int	code;
	int	check;

	check = check_args(args);
	ft_putendl_fd("exit", 1);
	if (check == -1)
	{
		ft_putendl_fd("minishoul: exit: too many arguments", 2);
		return (1);
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
