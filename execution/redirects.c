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

/**
 * Checks if input file exists and has r permissions, return exitfailure
 * else exitsuccess
 */
static int	check_input_redirs(t_node *cmd)
{
	t_node	*tmp;

	tmp = go_next_redir(cmd);
	while (tmp)
	{
		if (tmp->token_type == INPUT_REDIR)
		{
			if (!is_valid_read_or_exec_file(tmp->redir_path, 'r'))
				return (EXIT_FAILURE);
		}
		tmp = tmp->redirects;
	}
	return (EXIT_SUCCESS);
}

static int	precreate_output_files(t_node *cmd)
{
	t_node	*redir;
	int		fd;

	redir = go_next_redir(cmd);
	while (redir)
	{
		if (redir->token_type == OUTPUT_REDIR)
			fd = open(redir->redir_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->token_type == APP_OUT_REDIR)
			fd = open(redir->redir_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			redir = redir->redirects;
			continue ;
		}
		if (fd < 0)
			return (perror(redir->redir_path), EXIT_FAILURE);
		close(fd);
		redir = redir->redirects;
	}
	return (EXIT_SUCCESS);
}

/**
First loop through full cmd till/if pipe, check file access, if needed
create else print msg and exit If all well: start from left to
right exec cmds Bash first checks that input files exist and are readable.
If any input file is invalid, it aborts immediately — and does not
create or truncate output files.

----------------- todo ----------------------------------
handle < file, > fiule etc
if cmd_node = TOKEN_NULL: no cmd but <>>><< redir
<flie > cad, echo hi > nef >
> bla <b2 > b3
*/
int	apply_redirections(t_node *cmd)
{
	t_node	*redir;

	if (precreate_output_files(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_input_redirs(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	redir = go_next_redir(cmd);
	while (redir)
	{
		if (redir->token_type == INPUT_REDIR)
			try_redirect(redir, STDIN_FILENO, O_RDONLY);
		else if (redir->token_type == OUTPUT_REDIR)
			try_redirect(redir, STDOUT_FILENO, O_WRONLY | O_CREAT | O_TRUNC);
		else if (redir->token_type == APP_OUT_REDIR)
			try_redirect(redir, STDOUT_FILENO, O_WRONLY | O_CREAT | O_APPEND);
		redir = redir->redirects;
	}
	return (EXIT_SUCCESS);
}
