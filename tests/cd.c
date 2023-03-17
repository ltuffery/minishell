/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:43:55 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/17 15:43:55 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../src/builtins/pwd.c"

int	main(void)
{
	cd_builtins("/tmp");
	pwd_builtins();
	cd_builtins("/not_exist");
	pwd_builtins();
}
