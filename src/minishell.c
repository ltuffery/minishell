/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:13:10 by njegat            #+#    #+#             */
/*   Updated: 2023/03/28 19:49:37 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <bits/types/siginfo_t.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>

/*!------------------------ Fonction de Debug --------------------------!*/
void	print_struct(t_data *data)
{
	t_data	*tmp;
	tmp = data;
	while (tmp)
	{
		printf("\nData:------------------------\n");
		__builtin_dump_struct(tmp, &printf);
		int i = 0;
		printf("\nCmdx:------------------------\n");
		if (tmp->cmdx)
		{
			while (tmp->cmdx[i])
			{
				printf("%s - ", tmp->cmdx[i]);
				i++;
			}
		}
		printf("\n");
		while (tmp->file)
		{
			printf("\nFile:--------%p--------\n", tmp->file);
			__builtin_dump_struct(tmp->file, &printf);
			tmp->file = tmp->file->next;
		}
		tmp = tmp->next;
		printf("\n---------------------------------------------\n\n");
	}
}
/*!------------------------------ End ----------------------------------!*/
static void	cpy_env(char **env, t_env *my_env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		my_env->loc_env = ft_strappend(env[i], my_env->loc_env);
		i++;
	}
}

static void	input_handler(char *line, t_env *my_env)
{
	t_data	*data;

	data = NULL;
	if (!parsing_handler(line))
	{
		lexer_handler(&data, line, my_env);
		exec_handler(data, my_env);
	}
	//print_struct(data); // --> Debug - remove for push
	free_struct(&data);
}

static void	call_promt(char *line, t_env *my_env)
{
	if (line == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (line && *line)
	{
		input_handler(line, my_env);
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
		rl_replace_line("", 0);
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
	t_env	*my_env;

	my_env = malloc(sizeof(t_env));
	my_env->loc_env = NULL;
	cpy_env(env, my_env);
	(void)argv;
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
		line = readline("minishoul> ");
		call_promt(line, my_env);
	}
}
