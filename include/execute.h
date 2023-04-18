/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:16:30 by njegat            #+#    #+#             */
/*   Updated: 2023/04/18 16:53:55 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "minishell.h"
# include <fcntl.h>
# include <sys/wait.h>
# define EVEN 0
# define ODD 1
# define ERR_PIPE 12
# define ERR_DUP 13
# define ERR_FILE 14
# define CLOSE_FORK 7
# define CLOSE_P1 -3
# define CLOSE_P2 -4

void	exec_handler(t_data *data);
void	single_cmd(t_data *data);
int		pipe_handler(t_data *data);
int		heredoc_handler(char *limiter);
int		open_files(t_cmd *cmd);
int		open_heredoc(t_data *data);
void	close_files(t_cmd *cmd);
void	simple_dup_handler(t_cmd *cmd);
void	ft_print_error_cmd(char *cmd, int error_path, t_data *data);
void	ft_print_error_file(char *file);
void	ft_print_error_ambiguous(void);
int		get_cmd_path(t_data *data, t_cmd *cmd);
int		strcmp_strict(char *s1, char *s2);
int		select_pipe(t_data *data, t_cmd *cmd, int pos);
void	exit_fork(t_data *data);
void	close_all_files(t_data *data);
void	close_end_pipe(t_data *data, int pos);
void	close_pipe(t_data *data, t_cmd *cmd, int pos);
void	pipe_dup_handler(t_data *data, t_cmd *cmd, int pos);
int		is_builtins(t_cmd *cmd);
void	exec_pipe(t_data *data, t_cmd *cmd, int pos);
void	exec_pipe_builtins(t_data *data, t_cmd *cmd, int pos);

#endif
