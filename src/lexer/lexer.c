/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:39:07 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 19:29:01 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	lexer_handler(t_data **data, char *prompt, t_env *my_env)
{
	*data = cut_prompt(*data, prompt, my_env);
	files_handler(*data, my_env);
}
