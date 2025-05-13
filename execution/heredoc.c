/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 17:20:14 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/13 23:22:31 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	apply_heredoc(t_node *redir)
{
	int	fd;

	fd = open("heredoc_tmp.md", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror_and_return("-- check 1 ====heredoc_tmp.md"));
	write(fd, redir->heredoc_str, ft_strlen(redir->heredoc_str));
	close(fd);
	fd = open("heredoc_tmp.md", O_RDONLY);
	if (fd < 0)
		return (perror_and_return("--ch 2=======heredoc_tmp.md"));
	unlink("heredoc_tmp.md");
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), perror_and_return("ch 3--------heredoc dup2"));
	close(fd);
	return (EXIT_SUCCESS);
}
