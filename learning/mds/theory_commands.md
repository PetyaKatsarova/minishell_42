**TYPE utility**
how each argument would be interpreted if used as a command name:
type ls
ls is /usr/bin/ls

**WHICH**
returns  the  pathnames  of the files (or links) which would be executed in the
current environment, had its arguments been given as commands in a strictly POSIX-con‐
formant  shell.   It does this by searching the PATH for executable files matching the
names of the arguments.  It does not canonicalize path names.
which ls
/usr/bin/ls

**$?**
must be implemented
ls -a // returns exit status
echo $? prints that value (usually 0 if ls succeeded)
Track the last exit code (store in global or shell state)
Replace $? when parsing arguments (e.g., echo $?)
Reset it only after command runs
$ → means "expand a variable"
? → a special built-in variable that holds:
the exit status of the last command
Every command (builtin or external) returns a number when it finishes:
0 = success
1–255 = error / failure (meaning depends on the command)
Bash stores this number in $?.
ls
echo $?   # prints 0 if success
ls bad
echo $?   # prints non-zero (e.g. 2)
false
echo $?   # 1 (false always fails)
true
echo $?   # 0
After any command, set it to that return value
When user writes echo $?, replace $? with that number
=====================================================
**todo**
expand vars: 
echo $USER             # shows current user
echo $HOME/Desktop     # path expansion
cd $HOME               # use var in builtin
ls $PWD                # print current dir contents
export PATH=$PATH:/new # reuse existing value
env | grep $USER       # search env for yourself

You must increment SHLVL on shell startup.”
You must increment SHLVL on shell startup.”

1. Detect and expand variables before execution
After reading a line from the user, and before running commands:

expanded_input = expand_dollar_vars(raw_input, shell);
✅ 2. expand_dollar_vars() must:
🔹 Loop through input string:
For each char:

If it’s $, handle:
$? → insert itoa(shell->last_status)
$VAR → lookup in env_struct
If not, copy char as-is

echo $HOMEE
# → prints nothing (empty line)
If a parameter is not set, substitution shall result in an empty string.

📚 POSIX Shell Command Language – Section 2.6.2 Parameter Expansion
============================================================
