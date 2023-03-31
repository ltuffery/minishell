/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:13:10 by njegat            #+#    #+#             */
/*   Updated: 2023/03/31 16:28:45 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/lexer.h"
#include "../include/utils.h"
#include "../include/parsing.h"
#include "../include/signals.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <stdlib.h>

/*!------------------------ Fonction de Debug --------------------------!*/
void	print_struct(t_cmd *cmd)
{
	t_cmd	*tmp;
	tmp = cmd;
	while (tmp)
	{
		printf("\nData:------------------------\n");
		__builtin_dump_struct(tmp, &printf);
		int i = 0;
		printf("\nCmdx:------------------------\n");
		if (tmp->arg)
		{
			while (tmp->arg[i])
			{
				printf("%s - ", tmp->arg[i]);
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
static void	cpy_env(char **env, t_data *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		data->env = ft_strappend(env[i], data->env);
		i++;
	}
}

static void	input_handler(char *line, t_data *data)
{
	data->cmd = NULL;
	if (!parsing_handler(line))
	{
		lexer_handler(data, line);
		exec_handler(data);
	}
	//print_struct(data); // --> Debug - remove for push
	free_struct(&data->cmd);
	data->cmd = NULL;
}

static void	call_promt(char *line, t_data *data)
{
	if (line == NULL)
	{
		printf("exit\n");
		ft_double_free(data->env);
		exit(0);
	}
	if (line && *line)
	{
		input_handler(line, data);
		add_history(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	char				*line;
	t_data				data;

	(void)argv;
	data.env = NULL;
	init_signals(0);
	cpy_env(env, &data);
	if (argc != 1)
	{
		ft_putstr_fd("too many arguments", 2);
		return (0);
	}
	while (1)
	{
		line = readline("minishoul> ");
		call_promt(line, &data);
	}
}
