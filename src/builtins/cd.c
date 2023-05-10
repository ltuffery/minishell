/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:26:09 by ltuffery          #+#    #+#             */
/*   Updated: 2023/05/10 15:49:18 by njegat           ###   ########.fr       */
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

static void	pwd_change(t_data *data)
{
	char	**export;
	char	*tmp;
	char	pwd[PATH_MAX];

	tmp = getvalue(data->env, "PWD");
	if (!tmp)
		return ;
	free(tmp);
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

static void	oldpwd_change(t_data *data)
{
	char		**export;
	char		*tmp;
	static char	pwd_save[PATH_MAX];

	export = NULL;
	export = ft_strappend("export", export);
	export = ft_strappend("OLDPWD=", export);
	tmp = getvalue(data->env, "PWD");
	if (tmp)
		pwd_save[0] = 0;
	if (tmp)
		export[1] = ft_strjoin(export[1], tmp);
	else if (pwd_save[0])
		export[1] = ft_strjoin(export[1], pwd_save);
	if (export[1])
		export_builtins(export, data);
	if (!tmp)
	{
		if (getcwd(pwd_save, sizeof(pwd_save)) == NULL)
			perror("error pwd");
	}
	ft_double_free(export);
	free(tmp);
}

static int	puterror_cd(char *arg, int err)
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
	return (1);
}

static int	home_mana(char	*arg, t_data *data)
{
	int		error;
	char	*home;

	error = 0;
	home = getvalue(data->env, "HOME");
	if (!home)
	{
		error = puterror_cd("HOME", NSET);
		return (error);
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

int	cd_builtins(t_data *data, char **arg)
{
	int		error;

	if (arg[1])
	{
		if (arg[2])
		{
			ft_putendl_fd("minishoul: cd: too many arguments", 2);
			return (1);
		}
	}
	error = -1;
	if (arg[1] == NULL || arg[1][0] == '~')
		error = home_mana(arg[1], data);
	else
		error = chdir(arg[1]);
	if (error < 0)
		error = puterror_cd(arg[1], ERRDIR);
	if (error != 0)
		return (1);
	else
	{
		pwd_change(data);
		oldpwd_change(data);
	}
	return (error);
}
