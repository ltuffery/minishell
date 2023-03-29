/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_mana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:35:33 by njegat            #+#    #+#             */
/*   Updated: 2023/03/29 16:58:36 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	open_infile(t_cmd *cmd)
{
	t_file	*tmp;

	tmp = cmd->file;
	while (tmp)
	{
		if (tmp->type == INFILE)
		{
			tmp->fd = open(tmp->name, O_RDONLY, 0644);
			cmd->fd_infile = tmp->fd;
			if (tmp->fd == -1)
			{
				ft_print_error_file(tmp->name);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	open_heredoc(t_cmd *cmd)
{
	t_file	*tmp;

	tmp = cmd->file;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			//tmp->fd = get_here_doc();
			cmd->fd_infile = tmp->fd;
			if (tmp->fd == -1)
			{
				perror("minishoull: here_doc: ");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	open_out(t_cmd *cmd)
{
	t_file	*tmp;

	tmp = cmd->file;
	while (tmp)
	{
		if (tmp->type == OUTFILE || tmp->type == APPEND)
		{
			if (tmp->type == OUTFILE)
				tmp->fd = open(tmp->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			else if (tmp->type == APPEND)
				tmp->fd = open(tmp->name, O_APPEND | O_CREAT | O_WRONLY, 0644);
			cmd->fd_outfile = tmp->fd;
			if (tmp->fd == -1)
			{
				ft_print_error_file(tmp->name);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	open_files(t_cmd *cmd)
{
	int	infile_check;
	int	heredoc_check;
	int	out_check;

	heredoc_check = open_heredoc(cmd);
	infile_check = open_infile(cmd);
	out_check = open_out(cmd);
	if (heredoc_check || infile_check || out_check)
		return (1);
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
