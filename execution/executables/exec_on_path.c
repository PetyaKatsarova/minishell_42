/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_on_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:00:37 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/05 18:37:40 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Displays error message at fd 2(std err) and exits with code 127
 * Uses write because has single buffer, no random write from child processess
 */
static int	msg(char *name)
{
	size_t	len;
	char	*full;
	char	*tmp;

	full = ft_strjoin("Command '", name);
	if (!full)
		return (EXIT_CMD_NOT_FOUND);
	tmp = ft_strjoin(full, "' not found\n");
	free(full);
	if (!tmp)
		return (EXIT_CMD_NOT_FOUND);
	len = ft_strlen(tmp);
	write(STDERR_FILENO, tmp, len);
	free(tmp);
	return (EXIT_CMD_NOT_FOUND);
}

void	close_all_pipe_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
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

	if (!curr_cmd->argv[0] || curr_cmd->argv[0][0] == '\0')
		return (0);
	cmd_path = get_command_path(env_list, curr_cmd->argv[0]);
	if (!cmd_path)
	{
		env_list->last_exit_status = EXIT_CMD_NOT_FOUND;
		msg(curr_cmd->argv[0]);
		exit(EXIT_CMD_NOT_FOUND);
	}
	args = curr_cmd->argv;
	env = converted_env(env_list);
	if (!env)
		return (perror("Failed to convert environment variables."),
			free(cmd_path), EXIT_FAILURE);
	execve(cmd_path, args, env);
	perror("execve failed");
	free(cmd_path);
	free_t_env(env_list);
	exit(EXIT_FAILURE);
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
		if (pid == 0)
		{
			apply_redirections(curr_cmd);
			exec_command(env_list, curr_cmd);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			env_list->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			env_list->last_exit_status = 128 + WTERMSIG(status);
		return (env_list->last_exit_status);
	}
	exec_command(env_list, curr_cmd);
	exit(EXIT_CMD_NOT_FOUND);
}
