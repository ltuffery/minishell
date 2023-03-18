/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:09:01 by njegat            #+#    #+#             */
/*   Updated: 2023/03/18 13:45:00 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_struct(t_data **data)
{
	t_data	*tmp;

	while (*data)
	{
		ft_double_free((*data)->cmdx);
		if ((*data)->infile)
			free((*data)->infile);
		if ((*data)->outfile)
			free((*data)->outfile);
		tmp = (*data);
		*data = (*data)->next;
		free(tmp);
	}
}
