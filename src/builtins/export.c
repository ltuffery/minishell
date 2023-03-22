/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:23:30 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/22 20:57:36 by njegat           ###   ########.fr       */
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
	while (line[i] != '=')
		i++;
	var = malloc(sizeof(char) * (i + 1));
	if (var == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '=')
	{
		var[i] = line[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	**str_delete(char **str, char *delete)
{
	char	**new;
	int		i;
	int		j;

	if (!delete)
		return (NULL);
	new = malloc(ft_count(str) * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != delete)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = 0;
	free(delete);
	free(str);
	return (new);
}

void	printw_quote(char *line)
{
	char	*var;
	char	*tmp;

	var = getvar(line);
	if (!var)
		return ;
	tmp = getenv(var);
	if (!tmp)
		return ;
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(var, 1);
	printf("=\"%s\"\n", tmp);
	free(var);
}

static void	print_by_order(char **env)
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
		{
			printw_quote(tmp);
			//printf("declare -x %s\n", tmp);
		}
		old_env = env;
		env = str_delete(env, tmp);
	}
	ft_double_free(old_env);
}

static void	cpy_env(char **env, t_env *my_env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		my_env->loc_env = ft_strappend(env[i], my_env->loc_env);
		i++;
	}
}

char	**arr_cpy(char **arr)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc((ft_count(arr) + 1) * sizeof(char *));
	if (!new)
		return (new);
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = 0;
	return (new);
}

void	export_builtins(char **cmd, char **env, t_env *my_env)
{
	char	**tmp;
	
	if (!my_env->loc_env)
		cpy_env(env, my_env);
	tmp = arr_cpy(my_env->loc_env);
	if (ft_count(cmd) == 1)
		print_by_order(tmp);
}

int	main(int agrc, char **argv, char **env)
{
	t_env *my_env;

	my_env = malloc(sizeof(t_env));
	my_env->actual = NULL;
	my_env->loc_env = NULL;
	export_builtins(argv, env, my_env);
	ft_double_free(my_env->loc_env);
	free(my_env);
	return(0);
}
