/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:50:00 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/27 14:44:36 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H

# include <stddef.h>
# include "utils.h"
# include "../libft/libft.h"

typedef struct s_env
{
	char	**loc_env;
}	t_env;

void	echo_builtins(const char **argv);
void	cd_builtins(const char *path);
void	env_builtins(const char **env);
void	exit_builtins(void);
void	pwd_builtins(void);
// Export
void	export_builtins(char **cmd, char **env, t_env *my_env);
int		existing_var(char *line, t_env *my_env);
int		remove_plus(char *line);
char	**arr_cpy(char **arr);
char	**str_delete(char **str, char *delete);
void	print_by_order(char **env);
int 	parsing_var(char *line);

#endif
