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

