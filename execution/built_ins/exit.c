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
test: exit // exit, 0
exit 123 // exit, 123
exit bla 123 // exit, bash: exit: bla: numeric argument required, 2
exit 223 456 //exit
bash: exit: too many arguments, 1
exit 444444 // exit, 28
exit -33 // exit, 223
*/
#include <stdint.h>

/**
 * @brief Frees input, input_args, env_struct and clears history
 */
static void	free_exit_resources(char *input, char **input_args, t_env_list *env_struct)
{
	if (input)
	{
		free(input);
		input = NULL;
	}
	if (input_args)
	{
		free_arr(input_args);
		input_args = NULL;
	}
	if (env_struct)
	{
		free_t_env(env_struct);
		env_struct = NULL;
	}
	clear_history();
}

/**
 * @brief exit(exit_failure) & prints exit err and frees resources
 */
static void	handle_too_many_args(char *input, char **input_args, t_env_list *env_struct)
{
	print_builtin_error("exit", NULL, "too many arguments");
	free_exit_resources(input, input_args, env_struct);
	exit(EXIT_FAILURE);
}

/**
 * @brief Returns 1 if the argument is a valid exit argument (numeric), 0 otherwise.
 */
static int	is_valid_exit_arg(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	do_exit(char **input_args, char *input, t_env_list *env_struct)
{
	int	exit_status;

	if (env_struct->last_exit_status)
		exit_status = env_struct->last_exit_status;
	else
		exit_status = 0;
	write(STDERR_FILENO, "exit\n", 5);
	if (!input_args[1])
	{
		free_exit_resources(input, input_args, env_struct);
		exit(exit_status);
	}
	else if (input_args[1] && is_valid_exit_arg(input_args[1]))
	{
		if (input_args[2])
			handle_too_many_args(input, input_args, env_struct);
		exit_status = ft_atoi(input_args[1]) % 256; // bash returns between 0-255
	}
	else if (input_args[1])
	{
		write(STDERR_FILENO, "minisell: exit: ", 16);
		write(STDERR_FILENO, input_args[1], ft_strlen(input_args[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exit_status = 2;
	}
	free_exit_resources(input, input_args, env_struct);
	exit(exit_status);
}

/*
The exit status message should be sent to the standard error stream (stderr), not the standard output (stdout).

write() allows you to specify the file descriptor directly (STDERR_FILENO for error messages), ensuring that the message goes to the error stream.
Exit status 255: Commonly used for indicating an error or abnormal termination, but it is not defined by the system. Some programs or shells use 255 to signal specific conditions like:

A fatal error or critical failure in the program.

A "command not found" situation in shells like Bash (when the program cannot be located).

Programs that exit after receiving a signal or exception.

THEORY:
Interactive Shells:

Printing "exit" to stderr ensures that the message is visible to the user in the terminal, even if stdout is redirected elsewhere.
STDERR_FILENO:

STDERR_FILENO is a predefined constant in <unistd.h> that represents the file descriptor for standard error (usually 2).
Using write(STDERR_FILENO, ...) ensures that the message is sent to the terminal's error output stream.
*/
