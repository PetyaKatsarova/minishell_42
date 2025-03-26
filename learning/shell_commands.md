echo $SHELL

chmod +x filename // executable

The basic actions of the shell are simple. It reads a line. This is either from a file, a script, or from a user. First, meta-characters are "handled." Second, the name of the executable is found. Third, the arguments are passed to the program. Fourth, the file redirection is setup. Lastly, the program is executed.

Examples of POSIX shell filename expansions
Pattern	Matches
*	Every file in the current directory
?	Files consisting of one character
??	Files consisting of two characters
??*	Files consisting of two or more characters
[abcdefg]	Files consisting of a single letter from a to g.
[gfedcba]	Same as above
[a-g]	Same as above
[a-cd-g]	Same as above
[a-zA-Z0-9]	Files that consist of a single letter or number
[!a-zA-Z0-9]	Files that consist of a single character not a letter or number
[a-zA-Z]*	Files that start with a letter
?[a-zA-Z]*	Files whose second character matches a letter.
*[0-9]	Files that end with a number
?[0-9]	Two character filename that end with a number
*.[0-9]	Files that end with a dot and a number


 IFS is a shell variable, not an environment variable, so:

bash
Copy
Edit
env | grep IFS
→ Nothing will show (unless you manually exported it, which is rare).

✅ To check IFS, use:
bash
Copy
Edit
echo "$IFS" | cat -A
This will show invisible characters:

space →
tab → ^I
newline → $

declare -p IFS
output:
typeset IFS=$' \t\n\C-@'

