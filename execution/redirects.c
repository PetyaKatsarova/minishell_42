/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 18:07:26 by pekatsar          #+#    #+#             */
/*   Updated: 2025/05/07 18:07:26 by pekatsar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	perror_and_return(const char *message)
{
	close_all_pipe_fds();
	if (message)
		perror(message);
	else
		perror("minishell");
	return (EXIT_FAILURE);
}

static int	try_redirect(t_node *redir, int fd_target, int flags)
{
	int	fd;

	fd = open(redir->redir_path, flags, 0644);
	if (fd < 0)
		return (perror_and_return(redir->redir_path));
	if (dup2(fd, fd_target) == -1)
		return (close(fd), perror_and_return(redir->redir_path));
	close(fd);
	return (EXIT_SUCCESS);
}

int	apply_redirections(t_node *cmd, int i)
{
	t_node	*redir;

	redir = go_next_redir(cmd);
	while (redir)
	{
		if (redir->token_type == INPUT_REDIR
			&& (!is_valid_read_or_exec_file(redir->redir_path, 'r')
				|| try_redirect(redir, STDIN_FILENO, O_RDONLY) == EXIT_FAILURE))
			return (close_all_pipe_fds(), EXIT_FAILURE);
		if (redir->token_type == OUTPUT_REDIR
			&& try_redirect(redir, STDOUT_FILENO, O_WRONLY
				| O_CREAT | O_TRUNC) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (redir->token_type == APP_OUT_REDIR
			&& try_redirect(redir, STDOUT_FILENO, O_WRONLY
				| O_CREAT | O_APPEND) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (redir->token_type == HEREDOC
			&& apply_heredoc(redir, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		redir = redir->redirects;
	}
	return (EXIT_SUCCESS);
}
