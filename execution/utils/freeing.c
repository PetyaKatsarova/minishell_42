/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   freeing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 16:00:28 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/02 18:41:02 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_arr(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_t_env(t_env_list *env_struct)
{
	size_t	i;

	if (!env_struct || !env_struct->vars)
		return ;
	i = 0;
	while (i < env_struct->size)
	{
		if (env_struct->vars[i].key)
		{
			free(env_struct->vars[i].key);
			env_struct->vars[i].key = NULL;
		}
		if (env_struct->vars[i].value)
		{
			free(env_struct->vars[i].value);
			env_struct->vars[i].value = NULL;
		}
		i++;
	}
	free(env_struct->vars);
	env_struct->vars = NULL;
	free(env_struct);
}
