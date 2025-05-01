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
	close_all_pipe_fds();
	if (message)
		perror(message);
	else
		perror("minishell");
	exit(exit_code);
}

static void	try_redirect(t_node *redir, int fd_target, int flags)
{
	int fd = open(redir->redir_path, flags, 0644);
	if (fd < 0 || dup2(fd, fd_target) == -1)
		perror_and_exit(redir->redir_path, EXIT_FAILURE);
	close(fd);
}

int apply_redirections(t_node *cmd)
{
	t_node *redir = go_next_redir(cmd);
	while (redir)
	{
		if (redir->token_type == TOKEN_INPUT_REDIRECT)
		{
			is_valid_read_or_exec_file(redir->redir_path, 'r');
			try_redirect(redir, STDIN_FILENO, O_RDONLY);
		}
		else if (redir->token_type == TOKEN_OUTPUT_REDIRECT)
		{
			{
				is_valid_read_or_exec_file(redir->redir_path, 'w');
				try_redirect(redir, STDIN_FILENO, O_RDONLY);
			}
		}
		else if (redir->token_type == TOKEN_APPEND_OUTPUT_REDIRECT)
		{
			is_valid_read_or_exec_file(redir->redir_path, 'w');
			try_redirect(redir, STDOUT_FILENO, O_WRONLY | O_CREAT | O_APPEND);
		}
		redir = redir->redirects;
	}
	return (EXIT_SUCCESS);
}

