/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:23:11 by njegat            #+#    #+#             */
/*   Updated: 2023/04/11 14:49:18 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../libft/libft.h"
# include "minishell.h"

void		free_struct(t_cmd **cmd);
char		*getvar(char *line);
int			var_is_equal(char *var_chr, char *var_env);
char		*getvalue(char **env, char *var);
void		set_code(int code, t_boolean is_set_by_signal);
void		set_if_sig_false(int code);
t_exitcode	*exitcode(void);

#endif
