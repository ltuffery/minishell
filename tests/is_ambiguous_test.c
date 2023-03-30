/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ambiguous_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:36:50 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/30 16:51:21 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	is_ambiguous(char *val)
{
	size_t	i;
	int		has_space;

	i = 0;
	has_space = 0;
	while (val[i] != '\0')
	{
		if (val[i] != ' ' && has_space)
			return (1);
		if (i >= 1)
		{
			if (val[i - 1] != ' ' && val[i] == ' ')
				has_space = 1;
		}
		i++;
	}
	return (0);
}

int	main(void)
{
	printf("%i\n", is_ambiguous("a b")); // wait : 1
	printf("%i\n", is_ambiguous("   a       b")); // wait : 1
	printf("%i\n", is_ambiguous("ab")); // wait : 0
	printf("%i\n", is_ambiguous("ab     ")); // wait : 0
	printf("%i\n", is_ambiguous("    ab")); // wait : 0
	printf("%i\n", is_ambiguous("   a b")); // wait : 1
	printf("%i\n", is_ambiguous("    ab   ")); // wait : 0
}
