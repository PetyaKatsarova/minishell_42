/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/02 13:34:25 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/09 15:36:36 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
replacing variables with their values
echo $HOME
/home/user

The parser scans the input string for $ followed by a valid variable name (letters, numbers, or _).
The variable name is extracted, and its value is looked up in the t_env_list structure (your environment list).
The $VARIABLE in the input string is replaced with its corresponding value.
If the variable does not exist, it is replaced with an empty string.

Special Cases:
$?: Expands to the exit status of the last executed command (stored in last_exit_status in your t_env_list).
$$: Expands to the process ID (PID) of the current shell.
*/

char **expand_input_args(char **input_args)
{
	//char **updated_input_args;

	// iter all args: 
	// if $? or $$(pid) or $valid_env_var substitute str with value, treat invalid $invalid_env_var as normal str, if nth replaced: return original inputargs, otherwise, return the new mallocd **str
	return (input_args);
}