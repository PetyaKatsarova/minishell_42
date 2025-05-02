/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 18:35:36 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/02 18:35:36 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int	fd;

	fd = open(redir->redir_path, flags, 0644);
	if (fd < 0 || dup2(fd, fd_target) == -1)
		perror_and_exit(redir->redir_path, EXIT_FAILURE);
	close(fd);
}

int	apply_redirections(t_node *cmd)
{
	t_node	*redir;

	redir = go_next_redir(cmd);
	while (redir)
	{
		if (redir->token_type == INPUT_REDIR)
		{
			is_valid_read_or_exec_file(redir->redir_path, 'r');
			try_redirect(redir, STDIN_FILENO, O_RDONLY);
		}
		else if (redir->token_type == OUTPUT_REDIR)
		{
			is_valid_read_or_exec_file(redir->redir_path, 'w');
			try_redirect(redir, STDOUT_FILENO,
				O_WRONLY | O_CREAT | O_TRUNC);
		}
		else if (redir->token_type == APP_OUT_REDIR)
		{
			is_valid_read_or_exec_file(redir->redir_path, 'w');
			try_redirect(redir, STDOUT_FILENO,
				O_WRONLY | O_CREAT | O_APPEND);
		}
		redir = redir->redirects;
	}
	return (EXIT_SUCCESS);
}
