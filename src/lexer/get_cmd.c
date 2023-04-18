/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:59:47 by njegat            #+#    #+#             */
/*   Updated: 2023/04/18 14:23:01 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static int	skip_redirect(char *cmd, int pos)
{
	while (is_chevron(cmd[pos]))
		pos++;
	while (cmd[pos] == ' ')
		pos++;
	while (cmd[pos] != ' ' && cmd[pos])
		pos++;
	while (cmd[pos] == ' ')
		pos++;
	return (pos);
}

// static void	add_unit(t_cmd *cmd, char *add, int *pos)
// {
// 	int	i;

// 	i = *pos;
// 	add[i] = 0;
// 	i = 0;
// 	//i = skip_set(add, " ");
// 	if (pos > 0)
// 	cmd->arg = ft_strappend(add, cmd->arg);
// 	*pos = 0;
// }

static void	add_units(t_cmd *cmd, char **adds)
{
	int	i;

	i = 0;
	while (adds[i] != NULL)
	{
		cmd->arg = ft_strappend(adds[i], cmd->arg);
		i++;
	}
	ft_double_free(adds);
}

// static int	insert_var(char *cmd, char *add, int *j, char **tmp)
// {
// 	int	i;

// 	i = var_len(cmd);
// 	if (!add)
// 		return (i);
// 	*tmp = ft_strjoin(*tmp, add);
// 	*j = ft_strlen(*tmp);
// 	free(add);
// 	return (i);
// }





static int	insert_var(char *cmd, char *add, char **tmp)
{
	int	i;

	i = var_len(cmd);
	if (!add)
		return (i);
	if (!*tmp)
	{
		*tmp = malloc(1);
		*tmp[0] = 0;
	}
	*tmp = ft_strjoin(*tmp, add);
	free(add);
	return (i);
}

static void	add_unit(t_cmd *cmd, char **add)
{
	cmd->arg = ft_strappend(*add, cmd->arg);
	free (*add);
	*add = NULL;
}

char	*add_c(char *str, char c)
{
	char	*out;
	int		i;

	if (!str)
	{
		out = malloc(sizeof(char) * 2);
		out[0] = c;
		out[1] = 0;
		return (out);
	}
	else
		out = malloc(sizeof(char) * ft_strlen(str) + 3);
	if (!out)
		return (NULL);
	ft_strlcpy(out, str, ft_strlen(str) + 1);
	i = 0;
	while (out[i])
		i++;
	out[i] = c;
	out[i + 1] = 0;
	free(str);
	return (out);
}

int	get_replace_var(t_cmd *cmd, char *new_cmd, char **env, char **tmp)
{
	char	*var;
	char	**split;
	int		skip;

	skip = 0;
	var = var_value(new_cmd, env);
	if (is_quote(0, 1) == EMPTY_QUOTE && is_ambiguous(var))
	{
		split = ft_split(var, ' ');
		free (*tmp);
		*tmp = NULL;
		add_units(cmd, split);
		skip = var_len(new_cmd);
		free(var);
	}
	else
	{
		skip = insert_var(new_cmd, var, tmp);
		if (is_quote(0, 1) == EMPTY_QUOTE && !var)
			skip += skip_set(new_cmd + skip, " ");
	}
	return (skip);
}

void	get_cmd(t_cmd *cmd, char *new_cmd, char **env)
{
	char	*tmp;
	int		i;

	new_cmd = ft_strtrim(new_cmd, " \t");
	if (!new_cmd)
		return ;
	//i = skip_set(new_cmd, " \t");
	i = 0;
	tmp = NULL;
	while (new_cmd[i])
	{
		if (is_quote(new_cmd[i], 0))
		{
			i++;
			if (!new_cmd[i])
				add_unit(cmd, &tmp);
		}
		else if (is_chevron(new_cmd[i]) && !is_quote(0, 1))
			i = skip_redirect(new_cmd, i);
		else if (new_cmd[i] == ' ' && !is_quote(0, 1))
		{
			add_unit(cmd, &tmp);
			i += skip_set(new_cmd + i, " \t");
		}
		else if (new_cmd[i] == '$' && is_quote(0, 1) != SIMPLE_QUOTE)
			i += get_replace_var(cmd, new_cmd + i, env, &tmp);
		else
			tmp = add_c(tmp, new_cmd[i++]);
	}
	if (tmp)
		add_unit(cmd, &tmp);
	free(tmp);
}





// void	get_cmd(t_cmd *cmd, char *new_cmd, char **env)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;
// 	char	*var;
// 	char	**split;

// 	i = 0;
// 	j = 0;
// 	tmp = malloc((ft_strlen(new_cmd) + 1) * sizeof(char));
// 	i += skip_set(new_cmd + i, " \t");
// 	while (1)
// 	{
// 		if (is_quote(new_cmd[i], 0))
// 			i++;
// 		else if (is_chevron(new_cmd[i]) && !is_quote(0, 1))
// 			i = skip_redirect(new_cmd, i);
// 		else if ((new_cmd[i] == ' ' || !new_cmd[i]) && !is_quote(0, 1))
// 		{
// 			add_unit(cmd, tmp, &j);
// 			i += skip_set(new_cmd + i, " ");
// 			if (!new_cmd[i])
// 				break ;
// 		}
// 		else if (new_cmd[i] == '$' && is_quote(0, 1) != SIMPLE_QUOTE)
// 		{
// 			var = var_value(&new_cmd[i], env);
// 			tmp[j] = 0;
// 			if (is_quote(0, 1) == EMPTY_QUOTE && is_ambiguous(var))
// 			{
// 				split = ft_split(var, ' ');
// 				j = 0;
// 				add_units(cmd, split);
// 				i += var_len(&new_cmd[i]);
// 				free(var);
// 			}
// 			else
// 			{
// 				i += insert_var(new_cmd + i, var, &j, &tmp);
// 				if (is_quote(0, 1) == EMPTY_QUOTE && !var)
// 					i += skip_set(new_cmd + i, " ");
// 			}
// 		}
// 		else
// 			tmp[j++] = new_cmd[i++];
// 	}
// 	//add_unit(cmd, tmp, &j);
// 	free(tmp);
// }
