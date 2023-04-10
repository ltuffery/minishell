/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_rename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:20:22 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/05 14:50:20 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

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

static char	*final_name(t_file *file, char **env)
{
	size_t	i;
	size_t	name_len;
	char	*new_name;
	char	*value;

	i = 0;
	name_len = ft_strlen(file->name);
	new_name = ft_calloc(sizeof(char), 1);
	if (new_name == NULL)
		return (NULL);
	while (file->name[i] != '\0')
	{
		if (file->name[i] == '$' && is_quote(0, 1) != SIMPLE_QUOTE
			&& file->type != HERE_DOC)
		{
			value = var_value(&file->name[i], env);
			if (value == NULL)
				continue ;
			if (is_quote(0, 1) == EMPTY_QUOTE)
				file->ambiguous = is_ambiguous(value);
			new_name = ft_strjoin(new_name, value);
			if (new_name == NULL)
				return (NULL);
			while (ft_isalnum(file->name[i + 1]) || file->name[i + 1] == '_')
				i++;
		}
		else if (!is_quote(file->name[i], 0))
			new_name = str_addchar(new_name, file->name[i]);
		i++;
	}
	free(file->name);
	return (new_name);
}

void	files_handler(t_data *data)
{
	t_file	*file;

	file = data->cmd->file;
	while (file != NULL)
	{
		file->ambiguous = FALSE;
		file->name = final_name(file, data->env);
		file = file->next;
	}
}
