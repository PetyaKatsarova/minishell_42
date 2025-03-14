/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 11:17:10 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/14 11:20:53 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>


// cc -Wall -Wextra -Werror main.c && ./a.out
int	main(int argc, char **argv)
{
	if (argc > 1)
		printf("Hello world. this is minishell...And you are %s\n", argv[1]);
	return (0);
}