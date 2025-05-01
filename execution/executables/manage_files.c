/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_files.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 11:33:51 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/01 17:28:14 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/**
 * zsh: permission denied: todo.md
 */

 static void print_msg_and_exit(char *file_name)
 {
	ft_putstr_fd("minihell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	exit(EXIT_FAILURE);
 }
/*
 * Checks if file exists and has the read or execute permissions.
 * Returns 1 if valid, otherwise exits with an error message and 0
 * You only need 1 mode permission for your purpose, not all 3
 */
int	is_valid_read_or_exec_file(char *file_name, char mode)
{
	if (mode == 'r' && (access(file_name, F_OK) != 0
			|| access(file_name, R_OK) != 0))
			print_msg_and_exit(file_name);
	if (mode == 'w' && (access(file_name, F_OK) != 0
			|| access(file_name, X_OK) != 0))
			print_msg_and_exit(file_name);
	if (mode == 'x' && (access(file_name, F_OK) != 0
			|| access(file_name, X_OK) != 0))
			print_msg_and_exit(file_name);
	return (1);
}