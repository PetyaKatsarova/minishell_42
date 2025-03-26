/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 11:17:10 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/26 17:41:25 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// sudo apt-get install libreadline-dev

static int handle_readline(t_env *env_struct)
{
	while (1)
	{
		char *input;
		char **input_args;
		
		input = readline("\033[1;34mminihell$\033[0m ");
		if (!input) // handle CTR+D
		{
			printf("exit with no input collected.\n");
			clear_history(); // for mem leaks
			return (EXIT_FAILURE); // NEED TO CLEAR ALL MALLOCS 
		}
		input_args = ft_split(input, ' ');
		if (!input_args)
		{
			//todo err handle and clear memory
			perror("failed to split read line input_args\n");
			free(input);
			return (EXIT_FAILURE);
		}
		if (*input) // DO I NEED hte if? and why *
			add_history(input);
		if (input_args[0])
		{
			if (input_args[0] && ft_strncmp(input_args[0], "exit", 5) == 0)
			{
				do_exit(input_args, input);
				return (0);
			}
			else if (ft_strncmp(input_args[0], "pwd", 3) == 0)
				get_pwd();
			else if (ft_strncmp(input_args[0], "cd", 2) == 0)
				do_cd(input_args, env_struct);
			else if (ft_strncmp(input_args[0], "env", 3) == 0)
				get_env(env_struct);
			else if (ft_strncmp(input_args[0], "echo", 4) == 0)
				do_echo(input_args);
			//else if (ft_strncmp(input_args[0], "export", 7) == 0)
				//do_export(input_args, env_struct);
			else
			{
				printf("under construction. but unstoppable ....\n");
				system(input); // just for testing
			}
		}
		free(input);
		free_arr(input_args);
	}
	return (0);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out

int main(int argc, char **argv, char **envp) {
	(void) argc;
	(void) argv;
	t_env *env_struct = copy_env(envp);
	handle_readline(env_struct);
	free_t_env(env_struct);
    return (0);
}
