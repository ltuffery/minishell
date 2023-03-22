/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:23:30 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/21 16:57:40 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../libft/libft.h"
#include "../../include/builtins.h"

static char	*getvar(char *line)
{
	int		i;
	char	*var;

	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	var = malloc(sizeof(char) * (i + 1));
	if (var == NULL)
		return (NULL);
	i = 0;
	while (ft_isalpha(line[i]))
	{
		var[i] = line[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

static void	print(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

static char	**order_by_name(char **env)
{
	char	**order;
	size_t	count;
	int		i;

	i = 0;
	count = ft_count(env);
	order = ft_calloc(sizeof(char *), (count + 1));
	if (order == NULL)
		exit(1);
	while (env[i] != NULL)
	{
		i++;
	}
	return (order);
}

void	export_builtins(char *arg, t_env *env)
{
	char		*var;

	if (env->total == NULL)
		env->total = order_by_name(env->base);
	if (arg == NULL)
	{
		print(env->total);
		return ;
	}
	var = getvar(arg);
	free(var);
}
