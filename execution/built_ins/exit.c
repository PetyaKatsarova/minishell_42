/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/26 11:43:52 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/01 18:18:51 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
f0r1s3% (echo hello; exit 42)
hello
f0r1s3% echo $?
42
In scripts or pipelines, exit codes control logic, retries, error messages, etc.
todo....
ls /etc
echo $?   # 0 → success

ls /no/such/dir
echo $?   # 2 → error
Used in scripts or interactive shells to terminate the process with a status:

bash
Copy
Edit
exit          # exits with the last command's status
exit 0        # success
exit 1        # failure
exit 42       # custom error
 Range of Exit Codes
Valid: 0–255

exit 256 → wraps to 0 (only 8 bits)

exit from its current execution environment with the exit status specified by the unsigned decimal integer n
which $? // Exit status of last command
Always stores the numeric return code (0 = success, non-zero = error)
*/

#include "../../includes/minishell.h"

// TODO: HANDLE THE EXIT STATUS CASES...
int	do_exit(char **input_args, char *input)
{
	free(input);
	free_arr(input_args);
	clear_history();
	return (EXIT_SPECIAL_EXIT);
}
