/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:23:11 by njegat            #+#    #+#             */
/*   Updated: 2023/03/29 16:50:18 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "lexer.h"

void	free_struct(t_cmd **data);
char	*getvar(char *line);
int		var_is_equal(char *var_chr, char *var_env);
char	*getvalue(char **env, char *var);

#endif