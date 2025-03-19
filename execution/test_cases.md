1. test exit with 4 options: exit, exit 1234, exit asdfdsf etc

2. cat | cat | ls

3. ls '-l''a'
ls -la
ls '-la'

4. exit
output: exit
exit 123
output: exit

5. echo ?$
output: ?$
echo $?
output: 0

6. exit 123
exit
echo $?
123
## theory: exit 123
exits the shell with an exit status of 123.
After exiting, you restart the shell (or a new session opened automatically).
The exit status of the last executed command is stored in $?.

6. env
//shlvl = 5 // num that should grow after exit and start ./minishell again


7. expr $? + $?
// 262

8. echo "kou kou: " > 1 > 2 > 3 > 4 > file.txt
cat 1
car file.txt

echo '$USER'
// $USER

9. echo "tra la la... " >> 1 >> 2 >> 3 >> 4 >> file.txt
cat 1
cat file.txt

10. tail -n 2 < file.txt

11. cat << STOPW
hello
world
from minihell :)
heredoc
STOPW

12. '""'

13. which ls
cd /usr/bin
./ls
cd ~

echo $PATH

14. cat file.txt | grep bla | more

/mnt/c/Users/pskpe/OneDrive/Desktop/minishell_42$ 


