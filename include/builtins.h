/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:50:00 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/27 16:04:24 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <stddef.h>

int		echo_builtins(char **argv);
int		cd_builtins(t_data *data, char **arg);
int		env_builtins(char **env);
void	exit_builtins(t_data *data, char **args);
int		unset_builtins(t_data *data, char **arg);
int		pwd_builtins(void);
int		export_builtins(char **cmd, t_data *data);

// Export
int		existing_var(char *line, char **env);
int		remove_plus(char *line);
char	**arr_cpy(char **arr);
char	**str_delete(char **str, char *delete);
void	print_by_order(char **env);
int		parsing_var(char *line);

#endif
