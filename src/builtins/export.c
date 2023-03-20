/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:23:30 by ltuffery          #+#    #+#             */
/*   Updated: 2023/03/20 13:04:52 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../../libft/libft.h"
#include "../../include/builtins.h"

static char *getvar(char *line)
{
    int     i;
    char    *var;

    i = 0;
    while (ft_isalpha(line[i]))
        i++;
    var = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (ft_isalpha(line[i]))
    {
        var[i] = line[i];
        i++;
    }
    var[i] = '\0';
    return (var);
}

static void print(char **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        printf("declare -x %s\n", env[i]);
        i++;
    }
}

void    export_builtins(char *arg, char **env)
{
    static char **save = NULL;
    char        *var;

    if (save == NULL)
        save = env;
    if (arg == NULL)
    {
        print(save);
        return ;
    }
    var = getvar(arg);
    ft_putendl_fd(var, 1);
    free(var);
}
