/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:16:30 by njegat            #+#    #+#             */
/*   Updated: 2023/03/29 16:50:31 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "builtins.h"
# include "lexer.h"
# include <fcntl.h>
# include <sys/wait.h>

void	exec_handler(t_cmd *data, t_env *my_env);
void	single_cmd(t_cmd *data, t_env *my_env);
int		open_files(t_cmd *data);
void	close_files(t_cmd *data);
void	simple_dup_handler(t_cmd *data);
void	ft_print_error_cmd(char *cmd, int error_path);
void	ft_print_error_file(char *file);
int		get_cmd_path(t_cmd *data, t_env *my_env);
int		strcmp_strict(char *s1, char *s2);
int		get_cmd_path(t_cmd *data, t_env *my_env);

#endif