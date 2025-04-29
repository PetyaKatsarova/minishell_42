/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_on_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 17:07:36 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/29 20:22:22 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Displays error message at fd 2(std err) and exits with code 127
 */
static int	msg(char *name, char *msg)
{
	(void) msg;
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("' not found\n", 2);
	return (EXIT_CMD_NOT_FOUND);
}

void close_all_pipe_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024) // skip stdin, stdout, stderr
	{
		close(fd);
		fd++;
	}
}

/**
 * Runs the binary on the given path: /bin/ls -l, uses execve(overwrites curr process)
 */
static int	exec_command(t_env_list *env_list, t_node *curr_cmd)
{
	char	*cmd_path;
	char	**args;
	char	**env;
	//int		i;

	if (!curr_cmd->argv[0] || curr_cmd->argv[0][0] == '\0')
		return (0); // when press enter, no command to execute
	cmd_path = get_command_path(env_list, curr_cmd->argv[0]);
	if (!cmd_path)
	{
		env_list->last_exit_status = EXIT_CMD_NOT_FOUND;
		msg(curr_cmd->argv[0], " command not found");
		// close_all_pipe_fds();
		exit (EXIT_CMD_NOT_FOUND);
	}
	args = curr_cmd->argv;
	//if (!args) todo...
	env = converted_env(env_list);
	if (!env)
	{
		perror("Failed to convert environment variables.");
		free(cmd_path);
		return (EXIT_FAILURE);
	}
	execve(cmd_path, args, env);
	perror("execve failed");
	free(cmd_path);
	free_t_env(env_list);
	exit (EXIT_FAILURE);
}
/**
 * If in pipe, execve() directly with exec_command, if not: fork and execve(exec_command)
 */
int	exec_on_path(t_env_list *env_list, t_node *curr_cmd, int is_pipe)
{
	pid_t	pid = -1;
	int		status = -1;

	(void)is_pipe;
	if (!is_pipe)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork failed");
			env_list->last_exit_status = EXIT_FAILURE;
			return (EXIT_FAILURE);
		}
		if (pid == 0)
		{
			apply_redirections(curr_cmd);
			exec_command(env_list, curr_cmd);
		}
		waitpid(pid, &status, 0); 
		// printf("exit st, execve: %d\n", status); // testing: remove later
		if (WIFEXITED(status))
			env_list->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			env_list->last_exit_status = 128 + WTERMSIG(status);
		return (env_list->last_exit_status);
	}
	else
	{
		exec_command(env_list, curr_cmd);
	}
		
	exit (EXIT_CMD_NOT_FOUND); // ?? do we need this?
}

