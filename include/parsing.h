/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:46:50 by njegat            #+#    #+#             */
/*   Updated: 2023/03/17 16:06:12 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../libft/libft.h"

int	parsing_handler(char *prompt);
int	check_quote(char *prompt);
int	check_pipe(char *prompt);

#endif