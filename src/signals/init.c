/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:49 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/31 17:03:08 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/types/siginfo_t.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	listen(int sig, siginfo_t *info, void *unused)
{
	(void)info;
	(void)unused;
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

static void	child_listen(int sig, siginfo_t *info, void *unused)
{
	(void)info;
	(void)unused;
	if (sig == SIGQUIT)
		printf("Quit (core dumped)\n");
}

void	init_signals(int who)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	if (who == 0)
		act.sa_sigaction = listen;
	else
	 	act.sa_sigaction = child_listen;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
