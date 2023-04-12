/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_mana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:35:33 by njegat            #+#    #+#             */
/*   Updated: 2023/04/11 16:54:30 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/lexer.h"
#include "../../include/utils.h"

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

int	open_heredoc(t_data *data)
{
	t_cmd	*tmp_cmd;
	t_file	*tmp_file;

	tmp_cmd = data->cmd;
	while (tmp_cmd)
	{
		tmp_file = tmp_cmd->file;
		while (tmp_file)
		{
			if (tmp_file->type == HERE_DOC)
			{
				if (tmp_file->ambiguous == TRUE)
				{
					ft_print_error_ambiguous();
					set_code(1, TRUE);
					return (1);
				}
				tmp_file->fd = heredoc_handler(tmp_file->name);
				tmp_cmd->fd_infile = tmp_file->fd;
				if (tmp_file->fd == -1)
				{
					perror("minishoull: here_doc");
					set_code(1, TRUE);
					return (1);
				}
			}
			tmp_file = tmp_file->next;
		}
		tmp_cmd = tmp_cmd->next;
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
	int		out_check;
	t_file	*file;

	file = cmd->file;
	while (file != NULL)
	{
		if (file->ambiguous == TRUE)
		{
			ft_print_error_ambiguous();
			return (1);
		}
		if (file->type == HERE_DOC)
			cmd->fd_infile = file->fd;
		infile_check = open_infile(file, &cmd->fd_infile);
		out_check = open_out(file, &cmd->fd_outfile);
		if (infile_check || out_check)
		{
			set_code(1, TRUE);
			return (1);
		}
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
