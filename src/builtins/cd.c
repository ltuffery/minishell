/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:26:09 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/21 16:37:27 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/utils.h"
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#define MANY_ARG 1
#define NSET 2
#define ERRDIR 3

void	pwd_change(t_data *data)
{
	char	**export;
	char	*tmp;
	char	pwd[PATH_MAX];

	export = NULL;
	export = ft_strappend("export", export);
	export = ft_strappend("OLDPWD=", export);
	tmp = getvalue(data->env, "PWD");
	export[1] = ft_strjoin(export[1], tmp);
	free(tmp);
	if (export[1])
		export_builtins(export, data);
	ft_double_free(export);
	export = NULL;
	export = ft_strappend("export", export);
	export = ft_strappend("PWD=", export);
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("error pwd");
	else
	{
		export[1] = ft_strjoin(export[1], pwd);
		export_builtins(export, data);
	}
	ft_double_free(export);
}

static void	puterror_cd(char *arg, int err)
{
	if (err == MANY_ARG)
		ft_putstr_fd("minishoul: cd: too many arguments\n", 2);
	else if (err == NSET)
	{
		ft_putstr_fd("minishoul: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(" not set\n", 2);
	}
	else if (err == ERRDIR)
	{
		ft_putstr_fd("minishoul: cd: ", 2);
		perror(arg);
	}
}

static int	home_mana(char	*arg, t_data *data)
{
	int		error;
	char	*home;

	error = 0;
	home = getvalue(data->env, "HOME");
	if (!home)
	{
		puterror_cd("HOME", NSET);
		return (0);
	}
	if (!arg)
		error = chdir(home);
	else
	{
		home = ft_strjoin(home, arg + 1);
		if (home)
			error = chdir(home);
	}
	free(home);
	return (error);
}

void	cd_builtins(t_data *data, char **arg)
{
	int		error;

	if (arg[1])
	{
		if (arg[2])
		{
			ft_putendl_fd("minishoul: cd: too many arguments", 2);
			return ;
		}
	}
	error = -1;
	if (arg[1] == NULL || arg[1][0] == '~')
		error = home_mana(arg[1], data);
	else
		error = chdir(arg[1]);
	if (error < 0)
		puterror_cd(arg[1], ERRDIR);
	else
		pwd_change(data);
}
