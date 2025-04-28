/**
 * 
 * ls | grep "test" | wc -l
 * 
 *  cat < input.txt > output.txt
    Reads from input.txt, writes to output.txt.

    echo hi > file1 > file2      # Only the last one should be effective (file2)

    echo hi >                   # Should print syntax error
    Empty redirection target

    > file                      # Should create/empty file
    >> file                     # Should create file

    export VAR=42 > out.txt     # `VAR` still set, but out.txt is touched

    !! (echo hi > file) runs the command in a subshell.
    The parentheses () create a new child shell.
    Inside that child shell: echo hi > file is executed.
    Redirection affects only the subshell, not the main shell.
    VAR=main
(echo hi > file; VAR=sub)
echo $VAR
➡ file gets hi, but VAR remains main in the main shell.

Each command node (t_node) can have a linked list of redirections:

Set via node->redirects (struct s_node *redirects)

Each redirect node has:

token_type: one of TOKEN_INPUT_REDIRECT, TOKEN_OUTPUT_REDIRECT, TOKEN_APPEND_OUTPUT_REDIRECT


open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644); // for overwrite
open(path, O_WRONLY | O_CREAT | O_APPEND, 0644); // for append

Flag	Meaning
O_WRONLY	Open the file write-only (no read access)
O_CREAT	Create the file if it does not exist
O_TRUNC	If the file exists, truncate it to 0 length (i.e. clear contents)
O_APPEND	Write operations will append to the end of the file (don't truncate)
open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
✅ Use this for echo hello > file

If file exists: it’s cleared (truncated) and then written to.

If not: it’s created with mode 0644
redir_path: file name
open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);


> before command: invalid (> file.txt ls)
empty file after > if nothing is wri
permissions: cannot read (<) or write (>/>>) without access
| needs both sides: cat | grep (OK) but | grep (error)
file descriptor overwrite: cat file.txt > file.txt (undefined)
wrong file: cat < nonexist.txt → error
multiple redirects: last one wins → echo hi > a > b → only b has "hi"
mix redirects: cat < input.txt> output.txt
spaces matter: cat<file.txt may fail depending on parser
 */

#include "../includes/minishell.h"

/**
 * closes all pipes fds
 */
void	perror_and_exit(const char *message, int exit_code)
{
	close_all_pipe_fds(); // check if not handles elsewhere todo...
	if (message)
		perror(message);
	else
		perror("minishell");
	exit(exit_code);
}

/**
 * Apply redirections before execve() or builtin execution.
 */
void	apply_redirections(t_node *cmd)
{
	t_node	*redir;
	int		fd;

	redir = cmd->redirects;
	while (redir)
	{
		fd = -1;
		if (redir->token_type == TOKEN_INPUT_REDIRECT)
		{
			if (access(redir->redir_path, F_OK) != 0 || access(redir->redir_path, R_OK) != 0)
				perror_and_exit(redir->redir_path, 1);
			fd = open(redir->redir_path, O_RDONLY);
		}
		else if (redir->token_type == TOKEN_OUTPUT_REDIRECT)
			fd = open(redir->redir_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->token_type == TOKEN_APPEND_OUTPUT_REDIRECT)
			fd = open(redir->redir_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			perror_and_exit(redir->redir_path, 1);
		if (redir->token_type == TOKEN_INPUT_REDIRECT)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				perror_and_exit("dup2 error (input)", 1);
		}
		else
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
				perror_and_exit("dup2 error (output)", 1);
		}
		close(fd);
		redir = redir->redirects;
	}
}


