/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:32:20 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 18:31:19 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../../include/builtins.h"

int	parsing_var(char *line)
{
	int	i;

	i = 0;
	if (ft_isdigit(line[i]))
	{
		printf("minishell: export: '%s': not a valid identifier\n", line);
		return (1);
	}
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	if (i == 0)
	{
		printf("minishell: export: '%s': not a valid identifier\n", line);
		return (1);
	}
	else if (line[i] == 0)
		return (0);
	else if ((line[i] != '=' && line[i] != '+') \
			|| (line[i] == '+' && line[i + 1] != '='))
	{
		printf("minishell: export: '%s': not a valid identifier\n", line);
		return (1);
	}
	return (0);
}
