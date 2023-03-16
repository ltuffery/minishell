/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:13:10 by njegat            #+#    #+#             */
/*   Updated: 2023/03/16 13:54:35 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishel.h"
#include <bits/types/siginfo_t.h>
#include <signal.h>
#include <stdlib.h>

static void	call_promt(void)
{
	char	*line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("minishoul>");
	if (line == NULL)
	{
		printf("\n");
		exit(0);
	}
	if (line && *line)
		add_history(line);
}

void	listen(int sig, siginfo_t *info, void *unused)
{
	(void)info;
	(void)unused;
	if (sig == SIGINT)
	{
		write(0, "\nminishoul>", 11);
	}
}

int	main(int argc, char **argv, char **env)
{
	struct sigaction	act;

	(void)argv;
	(void)env;
	if (argc != 1)
	{
		ft_putstr_fd("too many arguments", 2);
		return (0);
	}
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = listen;
	sigaction(SIGINT, &act, NULL);
	while (1)
		call_promt();
}
