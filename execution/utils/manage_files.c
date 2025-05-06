/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_files.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:06:57 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/06 11:02:59 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void print_file_error(char *file_name)
{
	ft_putstr_fd("minihell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL); // prints ": <error>\n" using errno
}

/*
 * Validates file access by mode:
 * - 'r': must exist + readable
 * - 'w': if exists, must be writable
 * - 'x': must exist + executable
 * Returns 1 on success, 0 on failure
 */
int	is_valid_read_or_exec_file(char *file_name, char mode)
{
	if (mode == 'r')
	{
		if (access(file_name, F_OK) != 0 || access(file_name, R_OK) != 0)
		{
			print_file_error(file_name);
			return (0);
		}
	}
	else if (mode == 'w')
	{
		if (access(file_name, F_OK) == 0 && access(file_name, W_OK) != 0)
		{
			print_file_error(file_name);
			return (0);
		}
	}
	else if (mode == 'x')
	{
		if (access(file_name, F_OK) != 0 || access(file_name, X_OK) != 0)
		{
			print_file_error(file_name);
			return (0);
		}
	}
	return (1);
}

