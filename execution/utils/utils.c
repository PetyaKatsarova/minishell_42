/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 18:36:40 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/06 10:16:40 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	too_many_args(char **input_args)
{
	int	i;

	i = 0;
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

int	err_malloc(t_env_list *cpy, char *msg)
{
	perror(msg);
	if (cpy)
		free_t_env(cpy);
	exit(EXIT_FAILURE);
}

void	malloc_protect(void *ptr)
{
	if (!ptr)
	{
		perror("minihell");
		exit(EXIT_FAILURE);
	}
}

/**
 * Exit-on-failure allocator
 * Safely allocate memory (malloc, strdup, strjoin, substr).
	If allocation fails → prints perror("minishell") and exits
 */
void	*xalloc(t_alloc_type type, void *a, void *b, size_t size)
{
	void	*result;

	if (type == ALLOC_MALLOC)
		result = malloc(size);
	else if (type == ALLOC_STRDUP)
		result = ft_strdup((char *)a);
	else if (type == ALLOC_STRJOIN)
		result = ft_strjoin((char *)a, (char *)b);
	else if (type == ALLOC_SUBSTR)
		result = ft_substr((char *)a, (unsigned int)(size_t)b, (size_t)size);
	else
		result = NULL;
	if (!result)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	return (result);
}
