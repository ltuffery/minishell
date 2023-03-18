/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:43:52 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/17 18:06:03 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	const char	*argv1[] = {"echo", "oui", "non", "test", NULL};
	const char	*argv2[] = {"echo", "--nnn", "oui", "non", "test", NULL};
	const char	*argv3[] = {"echo", "-nnn", "oui", "non", "test", NULL};

	echo_builtins(argv1);
	echo_builtins(argv2);
	echo_builtins(argv3);
}
