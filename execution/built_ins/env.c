/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/17 11:56:26 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/17 11:56:30 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
!!NB!!
_=/usr/bin/env_lst
Means the last command run was /usr/bin/env_lst, and _ was set to that.
echo hello world
echo $_
In Bash, the special variable _ holds:
The last argument to the last executed command.

**TODO**: check if is set to the last command
Handle Extra Arguments:

If the user passes extra arguments to the env command (e.g., env ls or env echo $HOME), you need to detect these arguments and execute the corresponding command using execve.
Error Handling:

You should handle cases where env_lst is NULL or improperly initialized.
Return Value:

The function currently always returns 0. You might need to return an appropriate error code if something goes wrong.
Special Variable _:

You need to ensure that the special variable _ is updated to the last executed command.
Test the get_env_lst function with and without extra arguments.
Ensure the _ variable is updated correctly after executing a command.

*/

int	get_env(t_env_list *env_struct)
{
	size_t	i;

	// Check for missing PATH
	i = 0;
	while (i < env_struct->size && ft_strncmp(env_struct->vars[i].key, "PATH", 4))
		i++;
	if (i == env_struct->size || !env_struct->vars[i].value)
	{
		write(STDERR_FILENO, "minihell: env: No such file or directory\n", 41); // TODO !! MINIHELL
		return (127);
	}

	i = 0;
	while (i < env_struct->size)
	{
		if (env_struct->vars[i].key && env_struct->vars[i].value)
			printf("%s=%s\n", env_struct->vars[i].key, env_struct->vars[i].value);
		i++;
	}
	return (EXIT_SUCCESS);
}
