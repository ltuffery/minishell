/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_mana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:35:33 by njegat            #+#    #+#             */
/*   Updated: 2023/03/30 17:59:34 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	open_infile(t_file *file, int *fd_infile)
{
	if (file->type == INFILE)
	{
		file->fd = open(file->name, O_RDONLY, 0644);
		*fd_infile = file->fd;
		if (file->fd == -1)
		{
			ft_print_error_file(file->name);
			return (1);
		}
	}
	return (0);
}

int	open_heredoc(t_file *file, int *fd_infile)
{
	if (file->type == HERE_DOC)
	{
		//tmp->fd = get_here_doc();
		*fd_infile = file->fd;
		if (file->fd == -1)
		{
			perror("minishoull: here_doc: ");
			return (1);
		}
	}
	return (0);
}

int	open_out(t_file *file, int *fd_outfile)
{
	if (file->type == OUTFILE || file->type == APPEND)
	{
		if (file->type == OUTFILE)
			file->fd = open(file->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		else if (file->type == APPEND)
			file->fd = open(file->name, O_APPEND | O_CREAT | O_WRONLY, 0644);
		*fd_outfile = file->fd;
		if (file->fd == -1)
		{
			ft_print_error_file(file->name);
			return (1);
		}
	}
	return (0);
}

int	open_files(t_cmd *cmd)
{
	int		infile_check;
	int		heredoc_check;
	int		out_check;
	t_file	*file;

	file = cmd->file;
	while (file != NULL)
	{
		heredoc_check = open_heredoc(file, &cmd->fd_infile);
		infile_check = open_infile(file, &cmd->fd_infile);
		out_check = open_out(file, &cmd->fd_outfile);
		if (heredoc_check || infile_check || out_check)
			return (1);
		file = file->next;
	}
	return (0);
}

void	close_files(t_cmd *cmd)
{
	t_file	*tmp;

	tmp = cmd->file;
	while (tmp)
	{
		if (tmp->fd >= 0)
			close(tmp->fd);
		tmp = tmp->next;
	}
}
