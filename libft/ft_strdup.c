/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 01:22:43 by njegat            #+#    #+#             */
/*   Updated: 2023/02/10 10:16:36 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*output;

	output = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!(output))
		return (NULL);
	ft_memcpy(output, s, ft_strlen(s));
	output[ft_strlen(s)] = 0;
	return (output);
}
