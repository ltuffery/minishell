/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:39:07 by njegat            #+#    #+#             */
/*   Updated: 2023/04/08 12:42:48 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	lexer_handler(t_data *data, char *prompt)
{
	char	*tmp_prompt;

	tmp_prompt = wildcard_handler(prompt);
	data->cmd = cut_prompt(data, tmp_prompt);
	free(tmp_prompt);
	files_handler(data);
}
