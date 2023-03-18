/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:13:10 by njegat            #+#    #+#             */
/*   Updated: 2023/03/18 15:31:18 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <bits/types/siginfo_t.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>

static void	input_handler(char *line, char **env)
{
	t_data	*data;

	data = NULL;
	if (!parsing_handler(line))
	{
		lexer_handler(&data, line, env);
	}

/*----------------------- Debug ------------------------*/
	t_data	*tmp;
	tmp = data;
	while (tmp)
	{
		int i = 0;
		while (tmp->cmdx[i])
		{
			printf("%s - ", tmp->cmdx[i]);
			i++;
		}
		if (tmp->infile)
		{for (int j=0; tmp->infile[j] != NULL; j++)
			printf("%s - ", tmp->infile[j]);}
		if (tmp->outfile)
		{for (int j=0; tmp->outfile[j] != NULL; j++)
			printf("%s - ", tmp->outfile[j]);}
		printf("\n");
		tmp = tmp->next;
	}
/*------------------------- End -------------------------*/

	free_struct(&data);
}

static void	call_promt(char *line, char **env)
{
	if (line == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (line && *line)
	{
		input_handler(line, env);
		add_history(line);
	}
}

void	listen(int sig, siginfo_t *info, void *unused)
{
	(void)info;
	(void)unused;
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

int	main(int argc, char **argv, char **env)
{
	struct sigaction	act;
	char				*line;

	(void)argv;
	(void)env;
	if (argc != 1)
	{
		ft_putstr_fd("too many arguments", 2);
		return (0);
	}
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = listen;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	while (1)
	{
		line = readline("minishoul>");
		call_promt(line, env);
	}
}
