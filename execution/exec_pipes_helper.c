/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:52:59 by pekatsar          #+#    #+#             */
/*   Updated: 2025/05/14 17:31:48 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_sig(int *status, bool *sig_received)
{
	if (*sig_received == false)
	{
		if (128 + WTERMSIG(*status) == 130)
		{
			*sig_received = true;
			write(1, "\n", 1);
		}
		if (128 + WTERMSIG(*status) == 131)
		{
			*sig_received = true;
			write(1, "Quit (core dumped)\n", 19);
		}
	}
}

int	wait_all(pid_t *pids, int count)
{
	int		i;
	int		status;
	bool	sig_received;

	status = 0;
	i = 0;
	sig_received = false;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		check_sig(&status, &sig_received);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

/**
 * in child process no need to free/close resources: the OS claims all after child exits
 */
void	handle_child(t_data *data)
{
	int	status;

	status = 0;
	if (!data->cmd)
		exit(127);
	if (data->i > 0 && data->pipes[data->i - 1])
		dup2(data->pipes[data->i - 1][0], STDIN_FILENO);
	if (data->i < data->pipe_count && data->pipes[data->i])
		dup2(data->pipes[data->i][1], STDOUT_FILENO);
	close_all_pipes(data->pipes, data->pipe_count);
	free(data->pids);
	if (apply_redirections(data->cmd) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	status = execute_builtin(data->cmd, data->tree, data->env);
	if (status != EXIT_CMD_NOT_FOUND)
		exit(status);
	exec_on_path(data->env, data->cmd, 1);
	exit(EXIT_CMD_NOT_FOUND);
}
