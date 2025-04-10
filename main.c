/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   main.c											 :+:	:+:			*/
/*													 +:+					*/
/*   By: marvin <marvin@student.42.fr>				+#+					 */
/*												   +#+					  */
/*   Created: 2025/03/14 11:17:10 by pekatsar	  #+#	#+#				 */
/*   Updated: 2025/04/10 13:36:26 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "includes/minishell.h"

// sudo apt-get install libreadline-dev

static int handle_readline(t_env_list *env_struct_lst)
{
	while (1)
	{
		char	*input;
		char	**input_args;
		
		input = readline("\033[1;34mminihell$\033[0m ");
		if (!input) // handle CTR+D
		{
			printf("exit with no input collected.\n");
			clear_history(); // for mem leaks
			free_t_env(env_struct_lst);
			return (EXIT_FAILURE); // NEED TO CLEAR ALL MALLOCS 
		}
		if (*input) // DO I NEED * and why
			add_history(input);
		input_args = ft_split(input, ' ');
		if (!input_args)
		{
			//todo err handle and clear memory
			perror("failed to split read line input_args\n");
			free(input);
			// free envstruct
			return (EXIT_FAILURE);
		}
		if (input_args[0])
		{
			env_struct_lst->last_exit_status = handle_builtins(input_args, env_struct_lst, input);
			if (env_struct_lst->last_exit_status == EXIT_FAILURE)
			{
				free(input);
				free_arr(input_args);
				free_t_env(env_struct_lst);
				return (EXIT_FAILURE);
			}
		}
		free_arr(input_args);
	}
	return (0);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out

int main(int argc, char **argv, char **envp) {
	(void) argc;
	(void) argv;
	t_env_list *env_struct_lst = copy_env(envp); 
	// todo: check if envstructlst is not null or err or empty.... protect
	handle_readline(env_struct_lst);
	free_t_env(env_struct_lst);
	return (0);
}
