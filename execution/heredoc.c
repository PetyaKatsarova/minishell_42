/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 17:20:14 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/15 17:01:22 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	apply_heredoc(t_node *redir, int i)
{
	int		fd;
	char	*name;

	name = ft_itoa(i);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (free(name), perror_and_return("apply_heredoc"));
	write(fd, redir->heredoc_str, ft_strlen(redir->heredoc_str));
	close(fd);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (free(name), perror_and_return("apply_heredoc"));
	unlink(name);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (free(name), perror_and_return("apply_heredoc"));
	}
	close(fd);
	free(name);
	return (EXIT_SUCCESS);
}
