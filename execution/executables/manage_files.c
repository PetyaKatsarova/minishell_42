/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_files.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:06:57 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/02 13:06:59 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_msg_and_exit(char *file_name)
{
	ft_putstr_fd("minihell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	exit(EXIT_FAILURE);
}

/*
 * Checks if file exists and has the read, write or execute permissions.
 * Returns 1 if valid, otherwise exits with an error message and 0
 */
int	is_valid_read_or_exec_file(char *file_name, char mode)
{
	if (mode == 'r' && (access(file_name, F_OK) != 0
			|| access(file_name, R_OK) != 0))
		print_msg_and_exit(file_name);
	if (mode == 'w' && (access(file_name, F_OK) != 0
			|| access(file_name, W_OK) != 0))
		print_msg_and_exit(file_name);
	if (mode == 'x' && (access(file_name, F_OK) != 0
			|| access(file_name, X_OK) != 0))
		print_msg_and_exit(file_name);
	return (1);
}
