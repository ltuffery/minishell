#include "../include/builtins.h"
#include "../src/builtins/env.c"
#include "../libft/libft.h"

int main(int ac, char **av, char **env)
{
    export_builtins("ZZ=oui", env);
    ft_putendl_fd("--------------------------------", 1);
    export_builtins(NULL, env);
}