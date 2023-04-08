/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:58:24 by njegat            #+#    #+#             */
/*   Updated: 2023/04/08 09:46:16 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

static void	heredoc_fd(int fd, char *limiter)
{
	char	*str;

	while (1)
	{
		str = ft_get_line(0);
		if (!str)
			break ;
		if (!ft_strncmp(str, limiter, ft_strlen(limiter)))
		{
			if (!ft_strncmp(str, limiter, ft_strlen(str) - 1))
				break ;
		}
		ft_putstr_fd(str, fd);
		free(str);
	}
	free(str);
}

int	heredoc_handler(char *limiter)
{
	unsigned int	randval;
	char			*rand_string;
	char			*r_string;
	int 			fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (-1);
	read(fd, &randval, sizeof(randval));
	close(fd);
	rand_string = ft_itoa(randval);
	if (!rand_string)
		return (-1);
	r_string = ft_strdup("/tmp/.heredoc_");
	r_string = ft_strjoin(r_string, rand_string);
	free(rand_string);
	if (!r_string)
		return (-1);
	fd = open(r_string, O_CREAT | O_WRONLY, 0644);
	if (fd >= 0)
	{
		heredoc_fd(fd, limiter);
		close(fd);
	}
	fd = open(r_string, O_RDONLY, 0644);
	unlink(r_string);
	free(r_string);
	return (fd);
}
