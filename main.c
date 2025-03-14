/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 11:17:10 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/14 17:46:34 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out

int main() {
    char *input = readline("tra la la: ");
    if (input && *input) { // Ensure input is not NULL or empty
        add_history(input); // Store input in history
        printf("You entered: %s\n", input);
        free(input);
    }
	//char *input;

	//while (1)
	//{
	//	input = readline("mini_shell>> "); // outputs the prompt
	//	if (!input) // handle CTR+D
	//	{
	//		ft_printf("exit\n");
	//		break; // need to clear all malloc for later..
	//	}
	//}
    return (0);
}
