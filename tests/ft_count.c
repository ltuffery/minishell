/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:08:54 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/21 16:11:41 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stddef.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	size_t	i;

	(void) ac;
	(void) av;
	i = ft_count(env);
	printf("\n%zu\n", i);
}
