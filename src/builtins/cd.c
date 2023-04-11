/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:26:09 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/11 19:40:14 by ltuffery         ###   ########.fr       */
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
	char	*home;

	if (arg[2])
	{
		ft_putendl_fd("minishoul: cd: too many arguments", 2);
		return ;
	}
	error = -1;
	home = getvalue(data->env, "HOME");
	if (home != NULL && (arg[1] == NULL || !ft_strcmp(arg[1], "~")))
		error = chdir(home);
	else
		error = chdir(arg[1]);
	free(home);
	if (error < 0)
		puterror_cd(arg[1], ERRDIR);
	else
		pwd_change(data);
}
