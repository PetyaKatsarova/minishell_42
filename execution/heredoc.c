/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:20:14 by pekatsar          #+#    #+#             */
/*   Updated: 2025/05/14 11:06:06 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	apply_heredoc(t_node *redir)
// {
// 	int	fd;

// 	fd = open("heredoc_tmp.md", O_CREAT | O_WRONLY | O_TRUNC, 0600);
// 	if (fd < 0)
// 		return (perror_and_return("-- check 1 ====heredoc_tmp.md"));
// 	write(fd, redir->heredoc_str, ft_strlen(redir->heredoc_str));
// 	close(fd);
// 	fd = open("heredoc_tmp.md", O_RDONLY);
// 	if (fd < 0)
// 		return (perror_and_return("--ch 2=======heredoc_tmp.md"));
// 	unlink("heredoc_tmp.md");
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 		return (close(fd), perror_and_return("ch 3--------heredoc dup2"));
// 	close(fd);
// 	return (EXIT_SUCCESS);
// }
int	apply_heredoc(t_node *redir)
{
	static int	i = 0;
	char		name[20];
	int			fd;

	name[0] = 'h'; name[1] = 'd'; name[2] = '_';
	name[3] = '0' + i++; name[4] = 0;

	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (close_all_pipe_fds(), EXIT_FAILURE);
	write(fd, redir->heredoc_str, ft_strlen(redir->heredoc_str));
	close(fd);

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (close_all_pipe_fds(), EXIT_FAILURE);
	unlink(name);

	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), close_all_pipe_fds(), EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

