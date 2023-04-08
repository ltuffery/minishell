./minishell <test >minsh
bash <test >bsh
diff test minsh | grep \> | sed -e 's/> //g' >ret
diff bsh ret
