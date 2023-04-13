make re;
if [ "$1" -eq "1" ]
	then
		valgrind --suppressions=vsupp --track-fds=yes --leak-check=full --show-leak-kinds=all --trace-children=yes ./minishell;
	else
		./minishell;
fi
make fclean