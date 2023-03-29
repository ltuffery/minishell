/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:50:00 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/29 19:44:13 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H

# include <stddef.h>
# include "minishell.h"

void	echo_builtins(char **argv);
void	cd_builtins(const char *path);
void	env_builtins(char **env);
void	exit_builtins(t_data *data);
void	pwd_builtins(void);
// Export
void	export_builtins(char **cmd, char **env);
int		existing_var(char *line, char **env);
int		remove_plus(char *line);
char	**arr_cpy(char **arr);
char	**str_delete(char **str, char *delete);
void	print_by_order(char **env);
int 	parsing_var(char *line);

#endif
