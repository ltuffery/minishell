/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:26:09 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/11 15:38:17 by njegat           ###   ########.fr       */
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

void	cd_builtins(t_data *data, char **arg)
{
	int		error;
	char	*tmp;

	error = 0;
	if (arg[2])
		puterror_cd(NULL, MANY_ARG);
	else if (!arg[1] || !ft_strcmp(arg[1], "~"))
	{
		tmp = getvalue(data->env, "HOME");
		if (tmp)
		{
			error = chdir(tmp);
			free(tmp);
		}
		else
			puterror_cd("HOME", NSET);
	}
	else if (!ft_strcmp(arg[1], "-"))
	{
		tmp = getvalue(data->env, "OLDPWD");
		if (tmp)
		{
			error = chdir(tmp);
			pwd_builtins();
			free(tmp);
		}
		else
			puterror_cd("OLDPWD", NSET);
	}
	else
		error = chdir(arg[1]);
	if (error < 0)
		puterror_cd(arg[1], ERRDIR);
	else
		pwd_change(data);
}
