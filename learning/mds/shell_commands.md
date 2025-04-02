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

env | grep IFS
→ Nothing will show (unless you manually exported it, which is rare).

✅ To check IFS, use:

echo "$IFS" | cat -A
This will show invisible characters:

space →
tab → ^I
newline → $

declare -p IFS
output:
typeset IFS=$' \t\n\C-@'

---------------------------------------
$ = “expand this”
? = special variable holding the exit status of the last command
ls
echo $?   # → 0
false
echo $?   # → 1
$? is not stored in the environment — it's an internal shell state.
Use a global var:
int g_exit_status = 0;
Update:
After every builtin
After every external command
After exit (store the code before quitting)

🔹 2. Expand $? when parsing input
echo Hello $? World
# → echo Hello 0 World
You must:
Detect $? in the input
Replace it with itoa(g_exit_status)
Do this before executing builtins or forking

char *expand_dollars(const char *input)
{
    for each character in input:
        if '$' found:
            if next is '?'
                replace with g_exit_status
            else if valid env name
                replace with env var
        else
            copy char
}
**NEED TO IMPLEMENT EXPAND DOLLAR VARS
========
TODO: implement functionality for expanding: $var if in env and $? exit status from last command
 $? is not an environment variable
It’s internal shell state only
Bash does not show $? in env, export, or printenv
================================
SLINK
=====================================
touch original.txt
ln -s original.txt link.txt
Now:
cat link.txt  # shows contents of original.txt
But:
rm original.txt
cat link.txt  # broken symlink
A symbolic link, or symlink, is a special file that points to another file or directory by its path.

It's like:

📎 A shortcut on your desktop
🔁 A redirect to another file or folder
🧭 A reference that the OS follows when accessed

 Why Shells Need to Care
cd some_symlink_dir/.. might behave differently than cd actual_dir/..

Detect if a command or path is a symlink

Implement behavior like ls -l or realpath correctly

Use lstat() to print metadata for the symlink itself
mkdir real
ln -s real link

cd link
pwd        # resolves to full path of real

ls -l link # shows link -> real
Symlinks store a text path to another file/dir

They are created with ln -s

Use lstat() to detect them

They break if the target is deleted

Bash and all real shells handle them carefully — you should too ✅



