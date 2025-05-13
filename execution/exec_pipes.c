/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipes.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 15:55:03 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/02 15:55:03 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	exit_with_cleanup(t_data *data, int exit_code)
// {
// 	free_data(data);
// 	exit(exit_code);
// }

static void	exec_pipeline_fork(t_data *data, int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE); // cleanup ? 
	}
	else if (data->pids[i] == 0)
	{
		if (setup_signals_default() == -1)
			exit(EXIT_FAILURE); // cleanup ?
		handle_child(data);
	}
	else if (data->pids[i] > 0)
	{
		if (setup_sigint_ignore() == -1)
			exit(EXIT_FAILURE); // cleanup ?
		if (i > 0 && data->pipes[i - 1])
		{
			close(data->pipes[i - 1][0]);
			close(data->pipes[i - 1][1]);
		}
	}
}

static void	exec_pipeline_loop(t_data *data, t_node *cmd,
				t_env_list *env, t_tree *tree)
{
	int	i;

	i = 0;
	while (cmd)
	{
		setup_data_one(data, i, data->pipes, tree);
		setup_data_two(data, data->pids, cmd, env);
		if (i < data->pipe_count)
		{
			data->pipes[i] = malloc(sizeof(int) * 2);
			if (!data->pipes[i] || pipe(data->pipes[i]) < 0)
			{
				write(2, "pipe: error\n", 12);
				exit(EXIT_FAILURE); // cleanup ?
			}
		}
		exec_pipeline_fork(data, i);
		cmd = go_next_cmd(cmd);
		i++;
	}
	data->env->last_exit_status = wait_all(data->pids, i);
	if (setup_sigint_prompt() == -1)
		exit(EXIT_FAILURE); // cleanup?
}

int	exec_pipeline(t_env_list *env, t_tree *tree)
{
	t_data	data;
	t_node	*cmd;
	int		i;

	data.pipe_count = get_num_pipes(tree);
	data.pipes = malloc(sizeof(int *) * data.pipe_count);
	if (!data.pipes)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < data.pipe_count)
	{
		data.pipes[i] = NULL;
		i++;
	}
	data.pids = malloc(sizeof(pid_t) * (data.pipe_count + 1));
	if (!data.pids)
		exit(EXIT_FAILURE);
	cmd = go_first_cmd(tree);
	exec_pipeline_loop(&data, cmd, env, tree);
	close_all_pipes(data.pipes);
	free(data.pids);
	return (data.env->last_exit_status);
}
