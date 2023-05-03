/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:13:10 by njegat            #+#    #+#             */
/*   Updated: 2023/05/03 17:36:20 by njegat           ###   ########.fr       */
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
#include <limits.h>

static void	create_env(t_data *data)
{
	char	cwd[PATH_MAX];
	char	*tmp;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("error cwd");
	tmp = malloc(1);
	tmp[0] = 0;
	tmp = ft_strjoin(tmp, "PWD=");
	tmp = ft_strjoin(tmp, cwd);
	data->env = ft_strappend(tmp, data->env);
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
		set_code(2, FALSE);
	free_struct(&data->cmd);
	data->cmd = NULL;
}

static void	call_promt(char *line, t_data *data)
{
	int	code;

	if (line == NULL)
	{
		code = exitcode()->code;
		printf("exit\n");
		ft_double_free(data->env);
		free(exitcode());
		exit(code);
	}
	if (line && *line)
	{
		input_handler(line, data);
		add_history(line);
		exitcode()->write_by_signale = FALSE;
	}
}

char	*get_prompt(t_data *data)
{
	char	*out;
	char	*tmp;

	out = malloc(1);
	out[0] = 0;
	out = ft_strjoin(out, "\001\e[3;32m\002(\001\e[3;36m\002");
	tmp = getvalue(data->env, "USER");
	if (tmp != NULL)
		out = ft_strjoin(out, tmp);
	else
		out = ft_strjoin(out, "unnamed");
	free(tmp);
	out = ft_strjoin(out, "\001\e[3;32m\002)-[\001\e[0m\002");
	tmp = getvalue(data->env, "PWD");
	if (tmp != NULL)
		out = ft_strjoin(out, tmp);
	out = ft_strjoin(out, "\001\e[3;32m]\e[0m\002");
	free(tmp);
	out = ft_strjoin(out, "\n\001\e[3;36m\002minishoul> \001\e[0m\002");
	return (out);
}

int	main(int argc, char **argv, char **env)
{
	char				*line;
	t_data				data;
	char				*prompt;

	(void)argv;
	data.env = NULL;
	init_signals(PARENT);
	if (!env[0])
		create_env(&data);
	else
		cpy_env(env, &data);
	if (argc != 1)
	{
		ft_putstr_fd("too many arguments", 2);
		return (0);
	}
	while (1)
	{
		prompt = get_prompt(&data);
		line = readline(prompt);
		exitcode()->write_by_signale = FALSE;
		free(prompt);
		call_promt(line, &data);
	}
}
