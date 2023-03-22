/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:50:00 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/22 16:11:51 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H

# include <stddef.h>

typedef struct s_env
{
	char	**actual;
	char	**loc_env;
}	t_env;

void	echo_builtins(const char **argv);
void	cd_builtins(const char *path);
void	env_builtins(const char **env);
void	exit_builtins(void);
void	pwd_builtins(void);
void	export_builtins(char **cmd, char **env, t_env *my_env);

#endif
