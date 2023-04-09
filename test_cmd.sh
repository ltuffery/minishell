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
					err=0
					for nom in "no such file or directory\|No such file or directory" "command not found\|Command not found" "syntax error near unexpected token '>\|syntax error near unexpected token \`>" "syntax error near unexpected token '<\|syntax error near unexpected token \`<" "syntax error near unexpected token '|\|syntax error near unexpected token \`|"
					do
  						err1=`cat bsh | grep -a "$nom" | wc -l`
						err2=`cat ret | grep -a "$nom" | wc -l`
						#echo "err1 = $err1,  err2 = $err2,  nom = $nom\n"
						if ([ -s ret ] && [ -s bsh ]) && [ "$err1" -ne "$err2" ]
							then
								err=1
								echo "\033[0;31m"$ligne"\033[0m"
								echo "------------"
								cat <ret
								cat <bsh
								echo "----------\n\n"
								break
							else
								if ([ -s ret ] && [ -s bsh ]) && [ "$err1" -eq "1" ] && [ "$err2" -eq "1" ]
									then
										err=1
										break
									else
										err=0
								fi
						fi
					done
					if ([ -s ret ] && [ -s bsh ]) && [ "$err" -eq "0" ]
						then
							echo "\033[0;33m"$ligne"\033[0m"
							echo "------------"
							cat <ret
							cat <bsh
							echo "----------\n\n"
						else
							echo -n
					fi
					# if [ -s ret ] && [ -s bsh ] && [ "$err1" -ne "$err2" ]
					# 	then
					# 		echo "\033[0;33m"$ligne"\033[0m"
					# 		echo "------------"
					# 		cat <ret
					# 		cat <bsh
					# 		echo "----------\n\n"
					# 	else
					# 		echo -n
					# fi
				done;
			else
			echo "1 for back cmd and 2 for error"
		fi
fi

# && echo "pas vide" || echo "vide"