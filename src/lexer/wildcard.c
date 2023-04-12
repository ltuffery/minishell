/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:07:00 by njegat            #+#    #+#             */
/*   Updated: 2023/04/11 16:19:23 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include <dirent.h>

int	check_ext(char *file, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (file[i] && file[i] != str[0])
		i++;
	if (!file[i])
		return (0);
	j = 0;
	while (file[i] && file[i] == str[j])
	{
		if (!str[j])
			return (0);
		i++;
		j++;
	}
	if (!file[i] && !str[j])
		return (1);
	return (0);
}

char	*get_wildcard(char *str)
{
	struct dirent	*dir;
	char			*back;
	DIR				*d;

	back = malloc(1);
	back[0] = 0;
	d = opendir(".");
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (check_ext(dir->d_name, str))
			{
				if (dir->d_name[0] != '.')
				{
					back = ft_strjoin(back, dir->d_name);
					back = ft_strjoin(back, " ");
				}
			}
		}
		closedir(d);
	}
	return (back);
}

char	*str_add_c(char *str, char c)
{
	char	*out;
	int		i;

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

char	*get_ext(char *str)
{
	int		i;
	char	*out;

	i = 0;
	if (str[i] == '*')
		i++;
	out = malloc(1);
	if (!out)
		return (NULL);
	out[0] = 0;
	while (str[i] && str[i] != ' ')
	{
		out = str_add_c(out, str[i]);
		if (!out)
			return (NULL);
		i++;
	}
	return (out);
}

int	add_wildcard(char *str, char **prompt)
{
	char	*wildcard;
	char	*ext;
	int		i;

	i = 0;
	ext = get_ext(str);
	wildcard = get_wildcard(ext);
	if (wildcard[0])
	{
		*prompt = ft_strjoin(*prompt, wildcard);
		while (str[i] && str[i] != ' ')
			i++;
	}
	free(wildcard);
	free(ext);
	return (i);
}

static int	is_quote_tmp(char c, int get)
{
	static int	s_quote;
	static int	d_quote;

	if (get == 1)
	{
		if (s_quote)
			return (SIMPLE_QUOTE);
		else if (d_quote)
			return (DOOBLE_QUOTE);
		return (0);
	}
	if (c == '"' && s_quote == 0)
	{
		d_quote = !d_quote;
		return (1);
	}
	else if (c == '\'' && d_quote == 0)
	{
		s_quote = !s_quote;
		return (1);
	}
	return (0);
}

char	*wildcard_handler(char *str)
{
	int		i;
	char	*prompt;

	i = 0;
	prompt = malloc(1);
	prompt[0] = 0;
	while (str[i])
	{
		if (is_quote_tmp(str[i], 1) == 0)
		{
			if (str[i] == '*' && i == 0)
				i += add_wildcard(str + i, &prompt);
			else if (str[i] == '*' && str[i - 1] == ' ')
				i += add_wildcard(str + i, &prompt);
		}
		prompt = str_add_c(prompt, str[i]);
		i++;
	}
	return (prompt);
}
