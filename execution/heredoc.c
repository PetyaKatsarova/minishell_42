/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 17:20:14 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/10 13:42:29 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	apply_heredoc(t_node *redir)
{
	int	fd;

	fd = open("heredoc_tmp.md", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror_and_return("heredoc_tmp.md"));
	write(fd, redir->heredoc_str, ft_strlen(redir->heredoc_str));
	close(fd);
	fd = open("heredoc_tmp.md", O_RDONLY);
	write(1, "loc 1\n", 6);
	if (fd < 0)
		return (perror_and_return("heredoc_tmp.md"));
	write(1, "loc 3\n", 6);
	unlink("heredoc_tmp.md");
	write(1, "loc 3\n", 6);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), perror_and_return("heredoc dup2"));
	write(1, "loc 4\n", 6);
	close(fd);
	return (EXIT_SUCCESS);
}
