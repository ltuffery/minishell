/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:55:21 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/24 19:03:36 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execute.h"

int	heredoc_manager_call(t_file *file)
{
	if (file->ambiguous == TRUE)
	{
		ft_print_error_ambiguous();
		return (1);
	}
	file->fd = heredoc_handler(file->name);
	if (file->fd == -1)
		perror("minishoull: here_doc");
	return (file->fd);
}
