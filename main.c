/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 11:17:10 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/02 16:20:27 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// sudo apt-get install libreadline-dev

static int handle_readline(t_env_list *env_struct)
{
	while (1)
	{
		char	*input;
		char	*expanded_input_args;
		char	**input_args;
		int		exit_status = 1;
		
		input = readline("\033[1;34mminihell$\033[0m ");
		if (!input) // handle CTR+D
		{
			printf("exit with no input collected.\n");
			clear_history(); // for mem leaks
			free_t_env(env_struct);
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
		expanded_input_args = expand_input_args(input_args);
		if (expanded_input_args)
		{
			free(input);
			input = expanded_input_args;
		}
		if (ft_strcmp(input, "") == 0)
		{
			free(input);
			free_arr(input_args);
			continue;
		}
		if (*input) // DO I NEED hte if? and why *
			add_history(input);
		if (input_args[0])
		{
			exit_status = handle_builtins(input_args, env_struct, input);
			if (exit_status == EXIT_SPECIAL_EXIT)
				return (exit_status);
		}
		free_arr(input_args);
	}
	return (0);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out

int main(int argc, char **argv, char **envp) {
	(void) argc;
	(void) argv;
	t_env_list *env_struct = copy_env(envp);
	handle_readline(env_struct);
	free_t_env(env_struct);
    return (0);
}
