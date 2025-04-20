/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_on_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 17:07:36 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/20 10:29:35 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Displays error message at fd 2(std err) and exits with code 127
 */
static void	msg(char *name, char *msg)
{
	ft_putstr_fd("minihell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(name, 2);
	exit(EXIT_CMD_NOT_FOUND);
}

/**
 * Runs the binary on the given path: /bin/ls -l, uses execve(overwrites curr process)
 */
static void	exec_command(t_env_list *env_list, t_node *curr_cmd)
{
	char	*cmd_path;
	char	**args;
	char	**env;
	//int		i;

	if (!curr_cmd->argv[0] || curr_cmd->argv[0][0] == '\0')
		return ; // when press enter, no command to execute
	cmd_path = get_command_path(env_list, curr_cmd->argv[0]);
	if (!cmd_path)
	{
		env_list->last_exit_status = 127;
		printf("exec_command: %d\n", env_list->last_exit_status);
		msg(curr_cmd->argv[0], ": command not found ");
		// what we need to free here? todo...
		exit(127);
	}
	args = curr_cmd->argv;
	if (!args)
	{
		//helper_free(args, i, cmd_path);
		//	ASK JAN: DO STH: FREE_TREE(TREE)??
	}
	env = converted_env(env_list);
	if (!env) // todo: to handle later
	{
		perror("Failed to convert environment variables.");
		//free_args(args, i);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	printf("I am pid %d (parent: %d)\n", getpid(), getppid());

	execve(cmd_path, args, env);
	printf("I am pid %d (after execve parent: %d)\n", getpid(), getppid());

	perror("execve failed");
	//free_args(args, i);
	free(cmd_path);
	exit(EXIT_FAILURE);
}
/**
 * If in pipe, execve() directly with exec_command, if not: fork and execve(exec_command)
 */
int	exec_on_path(t_env_list *env_list, t_node *curr_cmd, int is_pipe)
{
	pid_t	pid;
	int		status;

	if (!is_pipe)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork failed");
			env_list->last_exit_status = 1;
			return (EXIT_FAILURE);
		}
		if (pid == 0)
			exec_command(env_list, curr_cmd);
		waitpid(pid, &status, 0); 
		printf("exit st, execve: %d\n", status); // testing: remove later
		if (WIFEXITED(status))
			env_list->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			env_list->last_exit_status = 128 + WTERMSIG(status);
		return (env_list->last_exit_status);
	}
	else
		exec_command(env_list, curr_cmd);
	return (EXIT_FAILURE);
}

