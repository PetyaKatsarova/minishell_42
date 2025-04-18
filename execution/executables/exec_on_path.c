/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_on_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 17:07:36 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/18 19:06:23 by pekatsar      ########   odam.nl         */
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
 * Executes the given command from the given path, handling errors appropriately.
 */
static void	exec_command(t_env_list *env_list, t_node *curr_cmd)
{
	char	*cmd_path;
	char	**args;
	char	**env;
	//int		i;

	if (!curr_cmd->argv[0] || curr_cmd->argv[0][0] == '\0') // why?? todo
	{
		ft_putendl_fd("pipex: permission denied:", 2);
		exit(127);
	}
	cmd_path = get_command_path(env_list, curr_cmd->argv[0]);
	if (!cmd_path)
	{
		msg(curr_cmd->argv[0], ": command not found ");
		free_t_env(env_list);
		//free_arr(curr_cmd->argv); todo: what needs to be freed?? JAN
		exit(EXIT_CMD_NOT_FOUND);
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
			return (EXIT_FAILURE);
		}
		if (pid == 0)
		{
			exec_command(env_list, curr_cmd);
		}
		waitpid(pid, &status, 0); 
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	else
	{
		exec_command(env_list, curr_cmd);
		// check what needs to be freed here... if execve fails...
	}
	return (EXIT_FAILURE);
}

