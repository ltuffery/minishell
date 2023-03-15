/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:46:42 by njegat            #+#    #+#             */
/*   Updated: 2023/02/14 19:36:57 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_new_line(int fd)
{
	char	*buff;
	char	*output;
	int		back;

	output = malloc(1);
	output[0] = 0;
	buff = malloc(2 * sizeof(char));
	buff[0] = 0;
	back = 1;
	while (!ft_strfind(output, '\n') && back > 0)
	{
		back = read(fd, buff, 1);
		if (back == -1)
		{
			free(output);
			free(buff);
			return (NULL);
		}
		buff[back] = 0;
		output = ft_strjoin(output, buff);
	}
	free(buff);
	return (output);
}

char	*ft_get_line(int fd)
{
	char	*output;

	if (fd < 0)
		return (NULL);
	output = ft_new_line(fd);
	if (!output)
		return (NULL);
	if (!*output)
	{
		free(output);
		output = NULL;
	}
	return (output);
}
