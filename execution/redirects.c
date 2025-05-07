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

/**
 * Exits with passed exit code after close all pipe fds and perror msg
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
//static int	check_input_redir(t_node *redir)
//{
//	if (redir->token_type == INPUT_REDIR)
//	{
//		if (!is_valid_read_or_exec_file(redir->redir_path, 'r'))
//			return (EXIT_FAILURE);
//	}
//	return (EXIT_SUCCESS);
//}

///**
// * Loops through all redirects;
// * if > creates the new file
// * if < none_ixistant file or no permission, stops execution and return exit failure/1
// */
//static int	precreate_output_files(t_node *cmd)
//{
//	t_node	*redir;
//	int		fd;

//	redir = go_next_redir(cmd);
//	while (redir)
//	{
//		if (check_input_redir(redir) == EXIT_FAILURE)
//			return (EXIT_FAILURE);	
//		else if (redir->token_type == OUTPUT_REDIR)
//			fd = open(redir->redir_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//		else if (redir->token_type == APP_OUT_REDIR)
//			fd = open(redir->redir_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
//		else
//		{
//			redir = redir->redirects;
//			continue ;
//		}
//		if (fd < 0)
//			return (perror(redir->redir_path), EXIT_FAILURE);
//		close(fd);
//		redir = redir->redirects;
//	}
//	return (EXIT_SUCCESS);
//}

/**
----------------- todo ----------------------------------
handle < file, > fiule etc
if cmd_node = TOKEN_NULL: no cmd but <>>><< redir
<flie > cad, echo hi > nef >
> bla <b2 > b3

pekatsar@f1r5s19:~/Desktop/minishell_42$ >newf > nf <nonex < no | echo bla > myf<noprint
bash: noprint: No such file or directory
bash: nonex: No such file or directory

*/
int	apply_redirections(t_node *cmd)
{
	t_node	*redir;

	//if (precreate_output_files(cmd) == EXIT_FAILURE)
	//	return (EXIT_FAILURE);
	redir = go_next_redir(cmd);
	while (redir)
	{
		//if (redir->token_type == INPUT_REDIR)
		//	try_redirect(redir, STDIN_FILENO, O_RDONLY);
		if (redir->token_type == INPUT_REDIR)
		{
			if (!is_valid_read_or_exec_file(redir->redir_path, 'r'))
				perror_and_exit(redir->redir_path, EXIT_FAILURE);
			try_redirect(redir, STDIN_FILENO, O_RDONLY);
		}
		else if (redir->token_type == OUTPUT_REDIR)
			try_redirect(redir, STDOUT_FILENO, O_WRONLY | O_CREAT | O_TRUNC);
		else if (redir->token_type == APP_OUT_REDIR)
			try_redirect(redir, STDOUT_FILENO, O_WRONLY | O_CREAT | O_APPEND);
		redir = redir->redirects;
	}
	return (EXIT_SUCCESS);
}
