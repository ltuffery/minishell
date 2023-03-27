/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_rename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:20:22 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/27 14:25:23 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static char	*str_addchar(char *str, char c)
{
	size_t	i;
	size_t	str_len;
	char	*new_str;

	i = 0;
	str_len = ft_strlen(str);
	new_str = ft_calloc(str_len + 2, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	free(str);
	return (new_str);
}

static char	*final_name(char *name)
{
	size_t	i;
	size_t	name_len;
	int		s_quote;
	int		d_quote;
	char	*new_name;
	char	*value;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	name_len = ft_strlen(name);
	new_name = ft_calloc(sizeof(char), 1);
	if (new_name == NULL)
		return (NULL);
	while (name[i] != '\0')
	{
		if (name[i] == '\'' && d_quote == 0)
			s_quote = !s_quote;
		if (name[i] == '"' && s_quote == 0)
			d_quote = !d_quote;
		if (name[i] == '$' && s_quote == 0)
		{
			value = var_value(&name[i]);
			if (value == NULL)
				continue ;
			new_name = ft_strjoin(new_name, value);
			if (new_name == NULL)
				return (NULL);
			while (ft_isalnum(name[i + 1]) || name[i + 1] == '_')
				i++;
		}
		else if (! is_quote(name[i], 0))
			new_name = str_addchar(new_name, name[i]);
		i++;
	}
	free(name);
	return (new_name);
}

void	files_handler(t_data *data)
{
	t_file	*file;

	file = data->file;
	while (file != NULL)
	{
		file->name = final_name(file->name);
		file = file->next;
	}
}
