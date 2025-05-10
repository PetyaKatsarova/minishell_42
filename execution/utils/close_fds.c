/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_fds.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 16:24:03 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/10 13:36:08 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
