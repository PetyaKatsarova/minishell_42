 
cmd < input.txt
Open input.txt for reading
Replace stdin (fd 0) with that file
cmd reads from input.txt instead of keyboard

Under the hood:

int fd = open("input.txt", O_RDONLY);
dup2(fd, STDIN_FILENO);  // redirects fd 0 to fd of the file
close(fd);
 cat < file.txt
file.txt opened
stdin redirected
cat reads from stdin, so it outputs contents of file.txt
 ============================================

 Parent Process:
    - readline
    - fork()
    - child:
        - apply_redirections()
        - execve()

Builtin commands (next to fix):
    - save stdin/stdout
    - apply_redirections()
    - run builtin
    - restore stdin/stdout


===================================================================
 tells bash (or minishell) to read the standard input (stdin) from the file infile instead of keyboard.

cat < infile
cat reads the contents of infile and prints them.

cat < infile
sort < data.txt
wc -l < words.txt
cat < infile | grep hello | wc -l
grep pattern < file.txt
sort < unsorted.txt > sorted.txt

===================================================
Wrong usages of <
 Redirect twice into stdin:
cat < infile < infile2
Problem: bash only uses the last < infile2 and ignores the first!

 Misplaced < inside filename:
cat in<file
Problem: Shell thinks <file is an input redirect! (syntax error)

 Redirect with no file:
cat <
Problem: Bash/minishell shows error:

bash: syntax error near unexpected token `newline'
 File does not exist:
cat < nonexistingfile
Problem: Bash shows error:

bash: nonexistingfile: No such file or directory
 In minishell you must print this exact same error to stderr!
 ====================================================
  Protect against these cases:

No filename after <

Empty spaces: cat <

Non-existing file after <

Multiple < in same command

< at the beginning with no command: < file

< followed by > or | without filename

Redirections must happen before executing the binary

Permission denied on file: cat < protected.txt if file is unreadable
===================================================
// minishell/src/exec/redirect.c

int handle_input_redirection(t_cmd *cmd) {
    int fd;

    if (!cmd->infile)
        return 0;

    fd = open(cmd->infile, O_RDONLY);
    if (fd < 0) {
        perror(cmd->infile);
        return -1;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return 0;
}
if (handle_input_redirection(cmd) < 0)
    return (1); // abort command if infile failed
parse redirections and apply them

if file failed to open → print error and skip everything

if OK, then execute the command (built-in or exec)

====================================================
cat < infile	open infile, dup2 to stdin, run cat
ls < notafile	error: notafile: No such file or directory
echo hello < file.txt	stdin replaced, echo runs
nosuchcmd < file.txt	open file.txt → OK, command fails: command not found
< file	error: syntax error near unexpected token
cat <	error: syntax error near unexpected token

============================================================