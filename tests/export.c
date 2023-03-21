#include "../include/builtins.h"
#include "../src/builtins/env.c"
#include "../libft/libft.h"
#include <stddef.h>

size_t	count(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

int	main(int ac, char **av, char **env)
{
	t_env	custom_env;

	custom_env.base = env;
	custom_env.total = NULL;
//	export_builtins("ZZ=oui", env);
//	ft_putendl_fd("--------------------------------", 1);
	export_builtins(NULL, &custom_env);
}
