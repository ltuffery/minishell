/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:13:10 by njegat            #+#    #+#             */
/*   Updated: 2023/04/04 14:48:52 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/lexer.h"
#include "../include/utils.h"
#include "../include/parsing.h"
#include "../include/signals.h"
#include "../include/builtins.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <stdlib.h>

int	g_status = 0;

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
	else
		g_status = 2;
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

char	*get_prompt(t_data *data)
{
	char	*out;
	char	*tmp;

	out = malloc(1);
	out[0] = 0;
	out = ft_strjoin(out, "\033[3;32m┌──(\033[0m\033[3;36m");
	tmp = getvalue(data->env, "USER");
	if (tmp)
		out = ft_strjoin(out, tmp);
	else
		out = ft_strjoin(out, "unnamed");
	free(tmp);
	out = ft_strjoin(out, "\033[0m\033[3;32m)-[\033[0m");
	tmp = getvalue(data->env, "PWD");
	if (tmp)
		out = ft_strjoin(out, tmp);
	out = ft_strjoin(out, "\033[3;32m]\033[0m");
	free(tmp);
	out = ft_strjoin(out, "\n\033[3;32m└─\033[0m\033[3;36mminishoul> \033[0m");
	return (out);
}

int	main(int argc, char **argv, char **env)
{
	char				*line;
	t_data				data;
	char				*promt;

	(void)argv;
	data.env = NULL;
	init_signals(PARENT);
	cpy_env(env, &data);
	if (argc != 1)
	{
		ft_putstr_fd("too many arguments", 2);
		return (0);
	}
	while (1)
	{
		promt = get_prompt(&data);
		line = readline(promt);
		free(promt);
		call_promt(line, &data);
	}
}
