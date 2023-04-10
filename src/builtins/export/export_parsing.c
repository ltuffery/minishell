/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:32:20 by njegat            #+#    #+#             */
/*   Updated: 2023/04/10 16:39:54 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../../include/builtins.h"

void	print_parsing(char *str)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

int	parsing_var(char *line)
{
	int	i;

	i = 0;
	if (ft_isdigit(line[i]))
	{
		print_parsing(line);
		return (1);
	}
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	if (i == 0)
	{
		print_parsing(line);
		return (1);
	}
	else if (line[i] == 0)
		return (0);
	else if ((line[i] != '=' && line[i] != '+') \
			|| (line[i] == '+' && line[i + 1] != '='))
	{
		print_parsing(line);
		return (1);
	}
	return (0);
}
