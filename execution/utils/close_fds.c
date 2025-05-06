/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_fds.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 16:24:03 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/06 16:24:44 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * . Bash and other shells use the same close(3..1023) logic
 * closing an already closed file descriptor does not cause an
 * error. It just returns -1 and sets errno = EBADF — meaning 
 * "Bad file descriptor" — but this is harmless unless you check
 *  close()'s return value and treat it as fatal.
 */
void	close_all_pipe_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}