/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   freeing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 16:00:28 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/13 17:44:15 by pekatsar      ########   odam.nl         */
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

/**
 * doesnt free data->cmd: it's shallow copy from tree
 */
void	free_data(t_data *data)
{
	if (!data)
		return;

	if (data->pipes)
	{
		close_all_pipes(data->pipes);
		data->pipes = NULL;
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (data->env)
	{
		free_t_env(data->env);
		data->env = NULL;
	}
	if (data->tree)
	{
		free_tree(data->tree);
		data->tree = NULL;
	}
	data->cmd = NULL;
}

/**
 * Frees all if available: t_tree, t_env_list, t_data, int **pipes
 */
void	total_liberation(t_tree *tree, t_env_list *env_list_struct, t_data *data, int **pipes)
{
	if (pipes)
		close_all_pipes(pipes);
	if (tree)
		free_tree(tree);
	if (env_list_struct)
		free_t_env(env_list_struct);
	if (data)
		free_data(data);
}
