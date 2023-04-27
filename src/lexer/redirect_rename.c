/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_rename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:20:22 by ltuffery          #+#    #+#             */
/*   Updated: 2023/04/27 08:52:10 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/lexer.h"

static void	get_value_var(t_file *file, int i, char **new_name, char **env)
{
	char	*value;

	value = var_value(&file->name[i], env);
	if (value == NULL)
		return ;
	if (is_quote(0, 1) == EMPTY_QUOTE)
		file->ambiguous = is_ambiguous(value);
	*new_name = ft_strjoin(*new_name, value);
}

static void	set_name_by_var(t_file *file, size_t i, char **new_name, char **env)
{
	char	*value;

	value = var_value(&file->name[i], env);
	if (value == NULL)
	{
		file->ambiguous = TRUE;
		return ;
	}
	if (is_quote(0, 1) == EMPTY_QUOTE)
		file->ambiguous = is_ambiguous(value);
	*new_name = ft_strjoin(*new_name, value);
	free(value);
	if (*new_name == NULL)
		return ;
	while (ft_isalnum(file->name[i + 1]) || file->name[i + 1] == '_')
		i++;
	get_value_var(file, i, new_name, env);
}

static char	*final_name(t_file *file, char **env)
{
	size_t	i;
	char	*new_name;

	i = 0;
	new_name = ft_calloc(sizeof(char), 1);
	if (new_name == NULL)
		return (NULL);
	while (file->name[i] != '\0')
	{
		if (file->name[i] == '$' && is_quote(0, 1) != SIMPLE_QUOTE
			&& file->type != HERE_DOC)
		{
			set_name_by_var(file, i, &new_name, env);
			i += var_len(&file->name[i]) - 1;
		}
		else if (!is_quote(file->name[i], 0))
			new_name = add_c(new_name, file->name[i]);
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
