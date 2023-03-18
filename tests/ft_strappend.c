#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

int	main(void)
{
	char	*add;
	char	**arr = NULL;

	add = malloc(sizeof(char) * 4);
	add[0] = 'o';
	add[1] = 'u';
	add[2] = 'i';
	add[3] = 0;
	arr = ft_strappend(add, arr);
	arr = ft_strappend(add, arr);
	for (int i = 0; arr[i] != NULL; i++)
		printf("%s\n", arr[i]);
	ft_double_free(arr);
	free(add);
}
