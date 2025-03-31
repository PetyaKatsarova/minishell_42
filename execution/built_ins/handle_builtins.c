/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_builtins.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/28 16:55:48 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/31 18:45:13 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Returns 0 if builtin was found and 1 or none zero inf command is not built in
It's normal for readline() to leave things in memory to speed up future calls or due to lazy cleanup.
*/
int	handle_builtins(char **input_args, t_env_list *env_struct, char *input)
{
	if (ft_strncmp(input_args[0], "exit", 5) == 0)
		return do_exit(input_args, input); 
	else if (ft_strncmp(input_args[0], "pwd", 4) == 0)
		get_pwd();
	else if (ft_strncmp(input_args[0], "cd", 3) == 0)
		do_cd(input_args, env_struct);
	else if (ft_strncmp(input_args[0], "env", 4) == 0)
		get_env(env_struct);
	else if (ft_strncmp(input_args[0], "echo", 5) == 0)
		do_echo(input_args);
	else if (ft_strncmp(input_args[0], "export", 7) == 0)
		do_export(input_args, env_struct);
	else
	{
		printf("under construction. but unstoppable ....\n");
		system(input); // just for testing
		return (EXIT_FAILURE); // none zero, usually 1
	}
		return (EXIT_SUCCESS); // 0
}
