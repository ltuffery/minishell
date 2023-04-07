/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:58:24 by njegat            #+#    #+#             */
/*   Updated: 2023/04/07 17:27:18 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

void	heredoc_fd(int fd, char *limiter)
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
