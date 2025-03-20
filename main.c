/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 11:17:10 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/20 15:02:48 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// sudo apt-get install libreadline-dev

static int handle_readline()
{
	while (1)
	{
		char *input = readline("minihell$ "); // outputs the prompt
		if (!input) // handle CTR+D
		{
			printf("exit\n");
			return (-1); 
			break; // need to clear all malloc for later..
		}
		if (*input)
			add_history(input);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			return (0); // free all later
			break;
		}
		else
		{
			// handle the entire program....
			//system(input); // handle if not valid command, no allowed func
			if (ft_strncmp(input, "pwd", 3) == 0)
				get_pwd();
			else
			{
				printf("under construction. but unstoppable ....\n");
			}
		}
		free(input);
	}
	return (0);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out

int main() {
	handle_readline();
    return (0);
}
