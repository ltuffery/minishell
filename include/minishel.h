/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:14:26 by njegat            #+#    #+#             */
/*   Updated: 2023/03/18 13:25:21 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "parsing.h"
# include "lexer.h"

typedef enum e_boolean
{
	FALSE = 0,
	TRUE = 1,
}	t_boolean;

void	free_struct(t_data **data);

#endif
