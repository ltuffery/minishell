/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:23:30 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/24 17:10:34 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../libft/libft.h"
#include "../../include/builtins.h"
#include "../../include/utils.h"


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

void	printw_quote(char **env, char *line)
{
	char	*var;
	char	*tmp;

	var = getvar(line);
	if (!var)
		return ;
	tmp = getvalue(env, var);
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(var, 1);
	if(line[ft_strlen(var)] == '=')
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
			printw_quote(env, tmp);
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








int parsing_var(char *line)
{
	int	i;

	i = 0;
	if (ft_isdigit(line[i]))
	{
		printf("minishell: export: '%s': not a valid identifier\n", line);
		return (1);
	}
	while(ft_isalnum(line[i]) || line[i] == '_')
		i++;
	if (i == 0)
	{
		printf("minishell: export: '%s': not a valid identifier\n", line);
		return (1);
	}
	else if (line[i] == 0)
		return (0);
	else if (line[i] != '=' && line[i] != '+')
	{
		printf("minishell: export: '%s': not a valid identifier\n", line);
		return (1);
	}
	if (line[i] == '+' && line[i + 1] != '=')
	{
		printf("minishell: export: '%s': not a valid identifier\n", line);
		return (1);
	}
	return (0);
}

int	existing_var(char *line, t_env *my_env)
{
	char	*value;
	char	*var;

	var = getvar(line);
	if (!var)
		return (0);
	value = getvalue(my_env->loc_env, var);
	free(var);
	if (!value)
		return (0);
	free(value);
	return (1);
}

int	remove_plus(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '+' && line[i] != '=')
		i++;
	if (line[i] != '+')
		return (0);
	while (line[i + 1])
	{
		line[i] = line[i + 1];
		i++;
	}
	line[i] = 0;
	return (1);
}

// void	add_var(char *line, t_env *my_env)
// {
// 	remove_plus(line);
// 	my_env->loc_env = ft_strappend(line, my_env->loc_env);
// }

char	*var_replace(char *line, char *var_env)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(line) + 1);
	if (!new)
		return (line);
	while (line[i] && line[i] != '=')
	{
		new[i] = line[i];
		i++;
	}
	if (!line[i])
	{
		new[i] = '=';
		new[i + 1] = 0;
		free(var_env);
		return (new);
	}
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	new[i] = 0;
	free(var_env);
	return (new);
}

char	*var_append(char *line, char *var_env)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	i++;
	new = malloc(((ft_strlen(var_env) + ft_strlen(line + i)) + 1) * sizeof(char));
	j = 0;
	while (var_env[j])
	{
		new[j] = var_env[j];
		j++;
	}
	while (line[i])
	{
		new[j] = line[i];
		i++;
		j++;
	}
	free(var_env);
	return (new);
}

void	modif_var(char *line, t_env *my_env)
{
	char	*var;
	int		i;

	var = getvar(line);
	i = 0;
	while (!var_is_equal(var, my_env->loc_env[i]))
		i++;
	if (!remove_plus(line))
		my_env->loc_env[i] = var_replace(line, my_env->loc_env[i]);
	else
		my_env->loc_env[i] = var_append(line, my_env->loc_env[i]);
	free(var);
	char** tmp = arr_cpy(my_env->loc_env);
	print_by_order(tmp);
	printf("Modif\n");
}

void arg_handler(char **cmd, t_env *my_env)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!parsing_var(cmd[i]))
		{
			if (!existing_var(cmd[i], my_env))
			{
				remove_plus(cmd[i]);
				my_env->loc_env = ft_strappend(cmd[i], my_env->loc_env);
			}
			else
				modif_var(cmd[i], my_env);
		}
		i++;
	}
}

void	export_builtins(char **cmd, char **env, t_env *my_env)
{
	char	**tmp;
	
	if (!my_env->loc_env)     // Probablement a faire en amont
		cpy_env(env, my_env); // edrftgtyhujik
	if (ft_count(cmd) == 1)
	{
		tmp = arr_cpy(my_env->loc_env);
		print_by_order(tmp);
	}
	else
		arg_handler(cmd, my_env);
}

// main remouve debug

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
