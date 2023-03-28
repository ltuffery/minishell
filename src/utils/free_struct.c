/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:09:01 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 12:25:12 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	free_struct(t_data **data)
{
	t_data	*tmp;
	t_file	*tmp_file;

	while (*data)
	{
		ft_double_free((*data)->cmdx);
		while ((*data)->file)
		{
			free((*data)->file->name);
			tmp_file = (*data)->file;
			(*data)->file = (*data)->file->next;
			free(tmp_file);
		}
		tmp = (*data);
		*data = (*data)->next;
		free(tmp);
	}
}

// void	free_env(t_env *my_env)
// {
// 	ft_double_free(my_env->loc_env);
// 	free(my_env);
// }
