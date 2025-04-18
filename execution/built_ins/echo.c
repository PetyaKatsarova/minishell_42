/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/17 11:56:12 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/17 11:56:15 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
echo -n // -n dont output the trailing newline, echo - display a line of text
Execute the echo command with or without arguments, or the -n option.
Repeat multiple times with different arguments.
*/

#include "../../includes/minishell.h"

/*
echo -n -nnnnnnnnnnnnnn bla: handle TODO undefined behavior
*/

/*
	Returns 1(true) if the string ends after ns and starts with -, otherwise 0(false).
*/
static int	is_echo_n_flag(char *str)
{
	size_t	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int	do_echo(char **argv)
{
	size_t	i;
	int		newline;

	i = 1;
	newline = 1;
	while (argv[i] && is_echo_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");

	return (EXIT_SUCCESS);
}
