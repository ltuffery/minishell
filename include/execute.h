/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:16:30 by njegat            #+#    #+#             */
/*   Updated: 2023/03/29 18:10:45 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "minishell.h"
# include <fcntl.h>
# include <sys/wait.h>

void	exec_handler(t_data *data);
void	single_cmd(t_data *data);
int		open_files(t_cmd *cmd);
void	close_files(t_cmd *cmd);
void	simple_dup_handler(t_cmd *cmd);
void	ft_print_error_cmd(char *cmd, int error_path);
void	ft_print_error_file(char *file);
int		get_cmd_path(t_data *data);
int		strcmp_strict(char *s1, char *s2);

#endif