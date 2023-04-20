/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:09:01 by njegat            #+#    #+#             */
/*   Updated: 2023/04/20 16:26:46 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	free_struct(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_file	*tmp_file;

	while (*cmd)
	{
		ft_double_free((*cmd)->arg);
		while ((*cmd)->file)
		{
			free((*cmd)->file->name);
			tmp_file = (*cmd)->file;
			(*cmd)->file = (*cmd)->file->next;
			free(tmp_file);
		}
		tmp = (*cmd);
		*cmd = (*cmd)->next;
		free(tmp);
	}
}
