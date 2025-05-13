/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_on_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:00:37 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/13 16:25:27 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**get_env_or_exit(t_env_list *env_list, char *cmd_path)
{
	char	**env;

	env = converted_env(env_list);
	if (!env)
	{
		perror("Failed to convert environment variables.");
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	return (env);
}

/**
 * Runs the binary on the given path: /bin/ls -l, uses
 * execve(overwrites curr process)
 */
static int	exec_command(t_env_list *env_list, t_node *curr_cmd)
{
	char	*cmd_path;
	char	**args;
	char	**env;

	cmd_path = NULL;
	args = NULL;
	env = NULL;
	if (!curr_cmd->argv[0] || curr_cmd->argv[0][0] == '\0')
		return (0);
	cmd_path = get_command_path(env_list, curr_cmd->argv[0]);
	if (!cmd_path)
	{
		env_list->last_exit_status = EXIT_CMD_NOT_FOUND;
		exit(EXIT_CMD_NOT_FOUND);
	}
	args = curr_cmd->argv;
	env = get_env_or_exit(env_list, cmd_path);
	execve(cmd_path, args, env);
	write(2, "minihell: execve failed\n", 25);
	free(cmd_path);
	free_t_env(env_list);
	exit(EXIT_FAILURE);
}

void	update_exit_status(t_env_list *env_list, int status)
{
	if (WIFEXITED(status))
		env_list->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		env_list->last_exit_status = 128 + WTERMSIG(status);
	if (128 + WTERMSIG(status) == 130)
		write(1, "\n", 1);
	if (128 + WTERMSIG(status) == 131)
		write(1, "Quit (core dumped)\n", 19);
}

/**
 * If in pipe, execve() directly with exec_command,
 * if not: fork and execve(exec_command)
 */
int	exec_on_path(t_env_list *env_list, t_node *curr_cmd, int is_pipe)
{
	pid_t	pid;
	int		status;

	pid = -1;
	status = -1;
	if (!is_pipe)
	{
		pid = fork();
		if (pid == -1)
			return (perror("minishell: fork failed"),
				env_list->last_exit_status = EXIT_FAILURE, EXIT_FAILURE);
		else if (pid == 0)
		{
			if (setup_signals_default() == -1)
				exit(EXIT_FAILURE); //cleanup ?
			if (apply_redirections(curr_cmd) != EXIT_SUCCESS)
				exit(EXIT_FAILURE);
			exec_command(env_list, curr_cmd);
		}
		else if (pid > 0)
		{
			if (setup_sigint_ignore() == -1)
				exit(EXIT_FAILURE); // cleanup ?
			waitpid(pid, &status, 0);
			if (setup_sigint_prompt() == -1)
				exit(EXIT_FAILURE); // cleanup ? 
			update_exit_status(env_list, status);
			return (env_list->last_exit_status);
		}
	}
	exec_command(env_list, curr_cmd);
	exit(EXIT_CMD_NOT_FOUND);
}
