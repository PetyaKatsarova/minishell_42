/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 17:38:18 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/13 17:40:58 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_data_one(t_data *data, int i, int **pipes, t_tree *tree)
{
	data->i = i;
	data->pipe_count = get_num_pipes(tree);
	data->pipes = pipes;
	data->tree = tree;
}

void	setup_data_two(t_data *data, pid_t *pids,
				t_node *cmd, t_env_list *env)
{
	data->pids = pids;
	data->cmd = cmd;
	data->env = env;
}