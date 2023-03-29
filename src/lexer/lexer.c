/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:39:07 by njegat            #+#    #+#             */
/*   Updated: 2023/03/29 17:07:42 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	lexer_handler(t_cmd **cmd, char *prompt, t_env *my_env)
{
	*cmd = cut_prompt(*cmd, prompt, my_env);
	files_handler(*cmd, my_env);
}
