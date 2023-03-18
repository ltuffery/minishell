/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:50:00 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/17 18:06:12 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	echo_builtins(const char **argv);
void	cd_builtins(const char *path);
void	env_builtins(const char **env);
void	exit_builtins(void);
void	pwd_builtins(void);

#endif
