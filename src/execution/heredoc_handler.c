/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:58:24 by njegat            #+#    #+#             */
/*   Updated: 2023/05/17 15:54:02 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/utils.h"
#include "../../libft/libft.h"

static void	heredoc_fd(int fd, char *limiter)
{
	char	*str;
	char	*stop_word;

	if (exitcode()->write_by_signale == TRUE)
		return ;
	stop_word = NULL;
	stop_word = ft_strdup(limiter);
	stop_word = add_c(stop_word, '\n');
	while (1)
	{
		ft_putstr_fd("here> ", 1);
		str = ft_get_line(0);
		if (!str)
			break ;
		if (!ft_strncmp(str, stop_word, ft_strlen(stop_word)))
		{
			if (!ft_strncmp(str, stop_word, ft_strlen(str) - 1))
				break ;
		}
		ft_putstr_fd(str, fd);
		free(str);
	}
	free(str);
	free(stop_word);
}

static char	*str_random(void)
{
	int				fd;
	unsigned int	random_nb;
	char			*output;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (NULL);
	read(fd, &random_nb, sizeof(random_nb));
	close(fd);
	output = ft_itoa(random_nb);
	return (output);
}

int	heredoc_handler(char *limiter)
{
	char	*random;
	int		fd;
	char	*rand_name;

	random = str_random();
	if (!random)
		return (-1);
	rand_name = ft_strdup("/tmp/.heredoc_");
	rand_name = ft_strjoin(rand_name, random);
	free(random);
	if (!rand_name)
		return (-1);
	fd = open(rand_name, O_CREAT | O_WRONLY, 0644);
	if (fd >= 0)
	{
		heredoc_fd(fd, limiter);
		close(fd);
	}
	fd = 0;
	if (exitcode()->write_by_signale == FALSE)
		fd = open(rand_name, O_RDONLY, 0644);
	unlink(rand_name);
	free(rand_name);
	return (fd);
}
