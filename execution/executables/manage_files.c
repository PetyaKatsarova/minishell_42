/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_files.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 11:33:51 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/26 21:28:06 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Checks if file exists and has the read or execute permissions.
 * Returns 1 if valid, otherwise exits with an error message and 0
 */
int	is_valid_read_or_exec_file(char *file_name, char mode)
{
	if (mode == 'r' && (access(file_name, F_OK) != 0
			|| access(file_name, R_OK) != 0))
	{
		perror("minihell");
		exit(EXIT_FAILURE);
	}
	if (mode == 'x' && (access(file_name, F_OK) != 0
			|| access(file_name, X_OK) != 0))
	{
		perror("minihell");
		exit(EXIT_FAILURE);
	}
	return (1);
}