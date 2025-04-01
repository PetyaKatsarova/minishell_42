/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 17:31:20 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/01 18:02:01 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Returns 1 if more than 2 args, 0 on 2 args
*/
int	too_many_args(char	**input_args)
{
	int	i = 0;
	while (input_args[i])
		i++;
	if (i > 2)
		return (1);
	return (0);
}

int	print_builtin_error(const char *cmd, const char *arg, const char *msg)
{
	if (msg)
	{
		if (arg)
		{
			printf("minishell: %s: %s: %s\n", cmd, arg, msg);
			return (EXIT_FAILURE);
		}
		printf("minishell: %s: %s\n", cmd, msg);
		return (EXIT_FAILURE);
	}
	if (arg)
	{
		printf("minishell: %s: %s: unknown error\n", cmd, arg);
		return (EXIT_FAILURE);
	}
	printf("minishell: %s: unknown error\n", cmd);
	return (EXIT_FAILURE);
}
