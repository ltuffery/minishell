/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:26:09 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/03 20:56:32 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/utils.h"
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

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

void	cd_builtins(t_data *data, char **arg)
{
	int		error;
	char	*tmp;

	if (!arg[1] || !ft_strcmp(arg[1], "~"))
	{
		tmp = getvalue(data->env, "HOME");
		error = chdir(tmp);
		free(tmp);
	}
	else if (arg[2])
	{
		ft_putstr_fd("minishoul: cd: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		return ;
	}
	else
		error = chdir(arg[1]);
	if (error < 0)
	{
		ft_putstr_fd("minishoul: cd: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		pwd_change(data);
	}
}
