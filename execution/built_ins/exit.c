/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   exit.c											 :+:	:+:			*/
/*													 +:+					*/
/*   By: marvin <marvin@student.42.fr>				+#+					 */
/*												   +#+					  */
/*   Created: 2025/03/26 11:43:52 by pekatsar	  #+#	#+#				 */
/*   Updated: 2025/04/09 11:03:28 by anonymous	 ########   odam.nl		 */
/*																			*/
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
exit		  # exits with the last command's status
exit 0		# success
exit 1		# failure
exit 42	   # custom error
 Range of Exit Codes
Valid: 0–255

exit 256 → wraps to 0 (only 8 bits)

exit from its current execution environment with the exit status specified by the unsigned decimal integer n
which $? // Exit status of last command
Always stores the numeric return code (0 = success, non-zero = error)

typedef struct s_env_list {
	t_env   *vars;
	int	 size;
	int	 capacity;
	int	 last_exit_status; //Every time a command runs → set shell->last_status = exit_code
} t_env_list;

  The exit utility shall cause the shell to exit from its current  execu‐
	   tion environment with the exit status specified by the unsigned decimal
	   integer n.  If the current execution environment is a subshell environ‐
	   ment, the shell shall exit from the subshell environment with the spec‐
	   ified exit status and continue in the environment from which that  sub‐
	   shell  environment was invoked; otherwise, the shell utility shall ter‐
	   minate with the specified exit status. If n is specified, but its value
	   is not between 0 and 255 inclusively, the exit status is undefined.

	   In Bash, if you write exit without specifying an exit status, the shell will exit with the exit status of the last executed command. This is the value stored in the special variable $?

	   In Bash, the behavior of exit when provided with a non-numeric argument is defined. Specifically, Bash will print an error message and exit with a status of 255. 
	   exit abc
	   bash: exit: abc: numeric argument required
		Interactive Shell (exit)	Prints "exit" before terminating.
		Subshell ((exit 42))	Does not print "exit".
		Script (./script.sh)	Does not print "exit".
	   */

#include "../../includes/minishell.h"

/*
Returns exit status: uint8_t only between 0 and 255
under and overflow: undefined behavior:exit -1 = 255
*/
#include <stdint.h>

/*
Mimics bash behavior for: returns 255 exit status if not valid numeric argument or out of range (0-255)
*/
static uint8_t validate_exit_status(const char *arg)
{
    unsigned long result = 0;
    int i = 0;

    if (arg[0] == '-' || arg[0] == '+')
    {
        if (arg[0] == '-')
            return (255);
        i++;
    }
    while (arg[i])
    {
        if (!ft_isdigit(arg[i]))
            return (255);
        result = result * 10 + (arg[i] - '0');
        if (result > 255)
            return (255);
        i++;
    }
    return ((uint8_t)result);
}

static void	free_exit_resources(char *input, char **input_args, t_env_list *env_struct)
{
	free(input);
	free_arr(input_args);
	clear_history();
	free_t_env(env_struct);
}

// handle invalid numeric arguments
static void	handle_invalid_exit_arg(char *input, char **input_args, t_env_list *env_struct, const char *arg)
{
	print_builtin_error("exit", arg, "numeric argument required");
	free_exit_resources(input, input_args, env_struct);
	exit(2);
}

// handle too many arguments
static int	handle_too_many_args(char *input, char **input_args)
{
	print_builtin_error("exit", NULL, "too many arguments");
	free(input);
	free_arr(input_args);
	clear_history();
	return (EXIT_FAILURE); // Do not exit the shell
}

int	do_exit(char **input_args, char *input, t_env_list *env_struct)
{
	int	exit_status;

	exit_status = env_struct->last_exit_status;
	if (env_struct->shlvl > 1)
		write(STDERR_FILENO, "exit\n", 5);
	// No arguments: exit with last status
	if (input_args[1] == NULL)
	{
		free_exit_resources(input, input_args, env_struct);
		exit(exit_status);
	}

	// Validate the first argument as an exit status
	exit_status = validate_exit_status(input_args[1]);
	if (exit_status == -1) // Invalid numeric argument
		handle_invalid_exit_arg(input, input_args, env_struct, input_args[1]);
	// Handle too many arguments
	if (input_args[2] != NULL)
		return (handle_too_many_args(input, input_args));

	// Free resources and exit with the specified status
	free_exit_resources(input, input_args, env_struct);
	// for debugging: todo: delete on production
	printf("exit status: %d\n", exit_status);
	exit(exit_status);
}

/*
THEORY:
Interactive Shells:

Printing "exit" to stderr ensures that the message is visible to the user in the terminal, even if stdout is redirected elsewhere.
STDERR_FILENO:

STDERR_FILENO is a predefined constant in <unistd.h> that represents the file descriptor for standard error (usually 2).
Using write(STDERR_FILENO, ...) ensures that the message is sent to the terminal's error output stream.
*/
