/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:39:07 by njegat            #+#    #+#             */
/*   Updated: 2023/03/21 18:44:10 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	lexer_handler(t_data **data, char *prompt, char **env)
{
	(void)env;
	*data = cut_prompt(*data, prompt);
	variable_handler(*data);
}
