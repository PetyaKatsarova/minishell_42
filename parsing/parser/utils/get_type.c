/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_type.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:18:05 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:18:06 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

static int	my_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	get_type(char *str)
{
	if (my_strcmp(str, "echo") == 0)
		return (ECHO);
	if (my_strcmp(str, "cd") == 0)
		return (CD);
	if (my_strcmp(str, "pwd") == 0)
		return (PWD);
	if (my_strcmp(str, "export") == 0)
		return (EXPORT);
	if (my_strcmp(str, "unset") == 0)
		return (UNSET);
	if (my_strcmp(str, "env") == 0)
		return (ENV);
	if (my_strcmp(str, "exit") == 0)
		return (EXIT);
	return (WORD);
}
