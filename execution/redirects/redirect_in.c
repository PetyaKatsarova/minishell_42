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

 */
#include "../../includes/minishell.h"
/**
 call this before execve() or execute_builtin()
 */
 void apply_redirections(t_node *cmd)
{
	t_node *redir = cmd->redirects;
	int fd;

	while (redir)
	{
		if (redir->token_type == TOKEN_INPUT_REDIRECT)
		{
			fd = open(redir->redir_path, O_RDONLY);
			if (fd < 0)
				perror_and_exit(redir->redir_path, 1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->token_type == TOKEN_OUTPUT_REDIRECT)
		{
			fd = open(redir->redir_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				perror_and_exit(redir->redir_path, 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->token_type == TOKEN_APPEND_OUTPUT_REDIRECT)
		{
			fd = open(redir->redir_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				perror_and_exit(redir->redir_path, 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->redirects;
	}
}
// test