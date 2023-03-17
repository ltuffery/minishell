/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:43:52 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/17 15:43:52 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	main(void)
{
	char	*argv[] = {"oui", "non", "test"};

	echo_builtins(3, argv, FALSE);
	echo_builtins(3, argv, TRUE);
}
