#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

int	main(void)
{
	char	*add;
	char	**arr;

	add = malloc(sizeof(char) * 4);
	add[0] = 'o';
	add[1] = 'u';
	add[2] = 'i';
	add[3] = 0;
	arr = ft_strappend(add, NULL);
	printf("%s | %s", arr[0], arr[1]);
}
