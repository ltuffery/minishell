/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:07:00 by njegat            #+#    #+#             */
/*   Updated: 2023/04/08 12:43:52 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <dirent.h>
#include <stdio.h>

int	check_ext(char *file, char	*str)
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
	 struct dirent *dir;
    char	*back;
	back = malloc(1);
	back[0] = 0;
    DIR *d = opendir("."); 
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
			if (check_ext(dir->d_name, str))
			{
           		back = ft_strjoin(back, dir->d_name);
				back = ft_strjoin(back, " ");
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
	while(out[i])
		i++;
	out[i] = c;
	out[i + 1] = 0;
	free(str);
	return (out);
}

char	*get_ext(char *str)
{
	int	i;
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

char	*wildcard_handler(char *str)
{
	int	i;
	char	*prompt;
	char	*wildcard;
	char	*ext;

	i = 0;
	prompt = malloc(1);
	prompt[0] = 0;
	while (str[i])
	{
		if (str[i] == '*')
		{
			ext = get_ext(str + i);
			wildcard = get_wildcard(ext);
			prompt = ft_strjoin(prompt, wildcard);
			free(ext);
			while (str[i] && str[i] != ' ')
				i++;
		}
		prompt = str_add_c(prompt, str[i]);
		i++;
	}
	return (prompt);
}
