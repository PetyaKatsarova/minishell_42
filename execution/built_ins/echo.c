/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 11:08:37 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/02 11:26:39 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Returns 1/true if the string ends after ns and starts with -,
	 otherwise 0/false.
*/
static int	is_echo_n_flag(char *str)
{
	size_t	i;

	i = 1;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

static void	write_str(const char *s)
{
	write(STDOUT_FILENO, s, ft_strlen(s));
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
		write_str(argv[i]);
		if (argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
