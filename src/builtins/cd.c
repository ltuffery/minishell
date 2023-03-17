/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:26:09 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/17 15:31:09 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	cd_builtins(const char *path)
{
	int	error;

	error = chdir(path);
	if (error < 0)
		perror("directory not found");
}
