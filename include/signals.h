/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:39:35 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/13 14:22:46 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

# define PARENT 0
# define DEFAULT 1
# define CHILD 2

void	init_signals(int who);

#endif
