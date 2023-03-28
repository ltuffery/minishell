/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:23:11 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 12:24:49 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "lexer.h"

void	free_struct(t_data **data);
char	*getvar(char *line);
int		var_is_equal(char *var_chr, char *var_env);
char	*getvalue(char **env, char *var);

#endif