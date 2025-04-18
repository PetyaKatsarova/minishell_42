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
//#include <stdint.h>

/**
 * Frees t_tree, env_struct_list and clears history
 */
static void	free_exit_resources(t_env_list *env_struct, t_tree *tree)
{

	free_tree(tree);
	free_t_env(env_struct);
	clear_history();
}

/**
 * Frees tree and env_struct, prints err exit(exit_failure) & prints exit err and frees resources
 */
static void	handle_too_many_args(t_env_list *env_struct, t_tree *tree)
{
	print_builtin_error("exit", NULL, "too many arguments");
	free_exit_resources(env_struct, tree);
	exit(EXIT_FAILURE);
}

/**
 * Returns 1 if the argument is a valid exit argument (numeric), 0 otherwise.
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

int	do_exit(t_env_list *env_struct, t_tree *tree, t_node *cmd_node)
{
	int	exit_status;

	if (env_struct->last_exit_status)
		exit_status = env_struct->last_exit_status;
	else
		exit_status = 0;
	write(STDERR_FILENO, "exit\n", 5);
	if (!cmd_node->argv[1])
	{
		free_exit_resources(env_struct, tree);
		exit(exit_status);
	}
	else if (cmd_node->argv[1] && is_valid_exit_arg(cmd_node->argv[1]))
	{
		if (cmd_node->argv[2])
			handle_too_many_args(env_struct, tree);
		exit_status = ft_atoi(cmd_node->argv[1]) % 256; // bash returns between 0-255
	}
	else if (cmd_node->argv[1])
	{
		write(STDERR_FILENO, "minisell: exit: ", 16);
		write(STDERR_FILENO, cmd_node->argv[1], ft_strlen(cmd_node->argv[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exit_status = 2;
	}
	free_exit_resources(env_struct, tree);
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
