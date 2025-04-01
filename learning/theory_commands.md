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
Track last_exit_code globally

After any command, set it to that return value

When user writes echo $?, replace $? with that number
