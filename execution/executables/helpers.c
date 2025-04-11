/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 11:30:57 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/11 11:33:03 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Frees a double pointer and its elements.
 */
void	free_dbl_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

/**
 * Frees allocated memory for the argv array.
 */
void	free_args(char **argv, int count)
{
	int	i;

	i = 1;
	while (i < count)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
