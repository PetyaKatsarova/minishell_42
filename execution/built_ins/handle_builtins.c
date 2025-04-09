/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_builtins.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/28 16:55:48 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/09 16:39:09 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Returns exit_status if builtin was found and func executed and 1 or none zero inf command is not built in
It's normal for readline() to leave things in memory to speed up future calls or due to lazy cleanup.
*/
int	handle_builtins(char **input_args, t_env_list *env_struct, char *input)
{
	int exit_status;

	exit_status = 0;
	if (ft_strncmp(input_args[0], "exit", 5) == 0)
		return do_exit(input_args, input, env_struct); // how abt shell in a shell, piped or not ?
	else if (ft_strncmp(input_args[0], "pwd", 4) == 0)
		exit_status = get_pwd();
	else if (ft_strncmp(input_args[0], "cd", 3) == 0)
		exit_status = do_cd(input_args, env_struct);
	else if (ft_strncmp(input_args[0], "env", 4) == 0)
		exit_status = get_env(env_struct);
	else if (ft_strncmp(input_args[0], "echo", 5) == 0)
		exit_status = do_echo(input_args);
	else if (ft_strncmp(input_args[0], "export", 7) == 0)
		exit_status = do_export(input_args, env_struct);
	else if (ft_strncmp(input_args[0], "unset", 6) == 0)
		exit_status = do_unset(input_args, env_struct);
	else
	{
		printf("under construction. but unstoppable ....\n");
		system(input); // just for testing
		return (EXIT_FAILURE); // none zero, usually 1
	}
	// for debugging: todo: delete on production
	printf("(exit status: %d)", exit_status);
	return (exit_status); // 0
}
