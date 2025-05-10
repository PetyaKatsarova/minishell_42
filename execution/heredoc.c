/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 17:20:14 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/09 21:34:19 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// if cmd_node = TOKEN_NULL: no cmd but <>>><< redir
// <flie > cad, echo hi > nef >
// todo: make it not static: Used in redirect.c too
static int	perror_and_return(const char *message)
{
	close_all_pipe_fds();
	if (message)
		perror(message);
	else
		perror("minishell");
	return (EXIT_FAILURE);
}

int apply_heredoc(t_node *redir)
{
    int fd;
    
    fd = open("heredoc_tmp.md", O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd < 0)
        return (perror_and_return("heredoc_tmp.md"));
    write(fd, redir->heredoc_str, ft_strlen(redir->heredoc_str));
    close(fd);
    fd = open("heredoc_tmp.md", O_RDONLY);
    if (fd < 0)
        return (perror_and_return("heredoc_tmp.md"));
    unlink("heredoc_tmp.md");
    if (dup2(fd, STDIN_FILENO) == -1)
        return (close(fd), perror_and_return("heredoc dup2"));
    close(fd);
    return (EXIT_FAILURE);
}
