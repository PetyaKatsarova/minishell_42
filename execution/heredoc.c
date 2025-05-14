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

int	apply_heredoc(t_node *redir, int i)
{
	int	fd;
	char *name = ft_itoa(i);

	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror_and_return(name));
	write(fd, redir->heredoc_str, ft_strlen(redir->heredoc_str));
	close(fd);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (perror_and_return(name));
	unlink(name);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), perror_and_return("heredoc dup2"));
	close(fd);
	return (EXIT_SUCCESS);
}
