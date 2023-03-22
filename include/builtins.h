/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:50:00 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/21 16:23:31 by ltuffery         ###   ########.fr       */
/*   Updated: 2023/03/21 17:53:16 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stddef.h>

typedef struct s_env
{
	char	**base;
	char	**total;
}	t_env;

void	echo_builtins(const char **argv);
void	cd_builtins(const char *path);
void	env_builtins(const char **env);
void	exit_builtins(void);
void	pwd_builtins(void);
void    export_builtins(char *arg, t_env *env);

#endif
