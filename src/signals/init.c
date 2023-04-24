/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:36:49 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/24 19:56:17 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signals.h"
#include "../../include/utils.h"
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
		set_code(130, TRUE);
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
	{
		printf("Quit (core dumped)\n");
		set_code(131, TRUE);
	}
	else if (sig == SIGINT)
		set_code(130, TRUE);
}

void	init_signals(int who)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_quit;

	ctrl_c.sa_flags = SA_SIGINFO;
	ctrl_quit.sa_flags = SA_SIGINFO;
	if (who == PARENT)
	{
		ctrl_quit.sa_handler = SIG_IGN;
		ctrl_c.sa_sigaction = listen;
	}
	else if (who == DEFAULT)
	{
		ctrl_c.sa_handler = SIG_DFL;
		ctrl_quit.sa_handler = SIG_DFL;
	}
	else if (who == CHILD)
	{
		ctrl_c.sa_sigaction = child_listen;
		ctrl_quit.sa_sigaction = child_listen;
	}
	sigemptyset(&ctrl_c.sa_mask);
	sigemptyset(&ctrl_quit.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
	sigaction(SIGQUIT, &ctrl_quit, NULL);
}
