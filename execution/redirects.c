/**
 * current = get_next_redir(current); // now current points to the first redir-node, then:
	current->redir_path // this will give you the path of the first redir
	current->token_type // this will give you the type of redir

	! in cat > newfile
	// bash waits for text to put into newfile, ctr+d=eof, ends input
 */

#include "../includes/minishell.h"

/**
 * closes all pipes fds and exits with the exit code
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
 * If redirection token: checks if valid fileredirects <,>,>>
 * todo: check valid redirect for cases like: cat < , < file, etc...
 */
void	apply_redirections(t_node *cmd)
{
	t_node	*redir;
	int		fd;

	redir = go_next_redir(cmd);
	while (redir)
	{
		fd = -1;
		if (redir->token_type == TOKEN_INPUT_REDIRECT)
		{
			is_valid_read_or_exec_file(redir->redir_path, 'r');
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
