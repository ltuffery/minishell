#./minishell <test >minsh
#bash <test >bsh
#diff test minsh | grep \> | sed -e 's/> //g' | sed -e 's/< //g' | sed "/┌─/d" | sed "/└─/d"  >ret
#diff bsh ret
if [ "$1" -eq "1" ]
	then
		cat test | while  read ligne ; do 
			echo $ligne >ret;
			./minishell <ret >minsh 2>tmp;
			bash <ret >bsh 2>tmp;
			cat minsh | sed "/┌─/d" | sed "/└─/d"  >ret
			if diff bsh ret
			then
				echo -n
			else
				echo "\033[0;31m"$ligne"\033[0m\n"
			fi
		done;
	else
		if [ "$1" -eq "2" ]
			then
				cat test | while  read ligne ; do 
					echo $ligne >ret;
					./minishell <ret 2>minsh 1>tmp;
					bash <ret 2>bsh 1>tmp;
					cat minsh | sed "/┌─/d" | sed "/└─/d"  >ret
					if [ -s ret ] && [ -s bsh ]
						then
							echo "\033[0;33m"$ligne"\033[0m"
							echo "------------"
							cat <ret
							cat <bsh
							echo "----------\n\n"
						else
							echo -n
					fi
				done;
			else
			echo "1 for back cmd and 2 for error"
		fi
fi

# && echo "pas vide" || echo "vide"