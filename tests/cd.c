/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:43:55 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/17 17:00:14 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"
#include "../src/builtins/pwd.c"

int	main(void)
{
	cd_builtins("/tmp");
	pwd_builtins();
	cd_builtins("/not_exist");
	pwd_builtins();
}
