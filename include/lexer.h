/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:54:11 by njegat            #+#    #+#             */
/*   Updated: 2023/04/24 16:44:02 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "minishell.h"

# define EMPTY_QUOTE 0
# define SIMPLE_QUOTE 1
# define DOOBLE_QUOTE 2

void	lexer_handler(t_data *data, char *prompt);
t_cmd	*cut_prompt(t_data *data, char *prompt);
void	get_redirect(t_cmd *add, char *new_cmd);
void	files_handler(t_data *data);
void	tokens_manager(t_cmd *cmd, char *new_cmd, char **env);

// utils
char	*str_addchar(char *str, char c);

// vars
char	*var_value(char *line, char **env);
int		is_ambiguous(char *val);
size_t	var_len(char *var);
int		variable(t_cmd *cmd, char *line, char **env, char **tmp);
char	*replace_variable(t_data *data, char *new_cmd);

#endif
