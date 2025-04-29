/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/18 15:13:09 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/26 08:27:41 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Returns 1/true if the string ends after ns and starts with -, otherwise 0/false.
*/
static int	is_echo_n_flag(char *str)
{
	size_t	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	if (str[1] != 'n')
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
