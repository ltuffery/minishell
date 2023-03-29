/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:14:26 by njegat            #+#    #+#             */
/*   Updated: 2023/03/29 16:46:53 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "parsing.h"
# include "lexer.h"
# include "builtins.h"
# include "utils.h"
# include "execute.h"

typedef enum e_boolean
{
	FALSE = 0,
	TRUE = 1,
}	t_boolean;


#endif
