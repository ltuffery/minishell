/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:54:11 by njegat            #+#    #+#             */
/*   Updated: 2023/04/17 18:37:49 by ltuffery         ###   ########.fr       */
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
void	get_cmd(t_cmd *cmd, char *new_cmd, char **env);
// utils
int		is_chevron(char c);
int		skip_set(char *str, char *set);
int		is_quote(char str, int get);
char	*str_addchar(char *str, char c);

// vars
char	*var_value(char *line, char **env);
int		is_ambiguous(char *val);
size_t	var_len(char *var);

char	*wildcard_handler(char *str);

#endif
