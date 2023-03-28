/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_mana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:35:33 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 15:59:05 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	open_in(t_data *data, t_file *file)
{
	if (file->type == INFILE)
		file->fd = open(file->name, O_RDONLY, 0644);
//	else if (file->type == HERE_DOC)
//		file->fd = get_here_doc();
	if (file->fd == -1)
	{
		perror("minishoull ");
		return (1);
	}
	data->fd_infile = file->fd;
	return (0);
}

int	open_out(t_data *data, t_file *file)
{
	if (file->type == OUTFILE)
		file->fd = open(file->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	else if (file->type == APPEND)
		file->fd = open(file->name, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (file->fd == -1)
		perror("minishoull ");
	data->fd_outfile = file->fd;
	return (0);
}

int	open_files(t_data *data)
{
	t_file	*tmp;

	tmp = data->file;
	while (tmp)
	{
		if (tmp->type == INFILE || tmp->type == HERE_DOC)
		{
			open_in(data, tmp);
		}
		else if (tmp->type == OUTFILE || tmp->type == APPEND)
		{
			open_out(data, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	close_files(t_data *data)
{
	t_file	*tmp;

	tmp = data->file;
	while (tmp)
	{
		if (tmp->fd >= 0)
			close(tmp->fd);
		tmp = tmp->next;
	}
}
