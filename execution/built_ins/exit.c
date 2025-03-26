/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/26 11:43:52 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/26 17:42:04 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
f0r1s3% (echo hello; exit 42)
hello
f0r1s3% echo $?
42
In scripts or pipelines, exit codes control logic, retries, error messages, etc.
todo....
*/

#include "../../includes/minishell.h"

int	do_exit(char **input_args, char *input)
{
	free(input);
	free_arr(input_args);
	clear_history();
	return (0);
}
