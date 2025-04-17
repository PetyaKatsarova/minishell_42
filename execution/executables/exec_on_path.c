/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_on_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 17:07:36 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/17 14:10:44 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Frees char **args and char *cmd_path, and exits with EXIT_FAILURE.
*/
static	void	helper_free(char **args, int i, char *cmd_path)
{
	perror("Failed to allocate memory for argument.");
	free_args(args, i);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

/**
 * Allocates and fills the argv array for execve based on the splitted_command array.
 */
static char	**prepare_command_args(char *cmd_path, char **splitted_cmd, int cnt)
{
	char	**args;
	int		i;

	args = malloc((cnt + 1) * sizeof(char *));
	if (!args)
	{
		perror("Failed to allocate memory for args.");
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	args[0] = cmd_path;
	i = 1;
	while (i < cnt)
	{
		(void)splitted_cmd;
		args[i] = ft_strdup(splitted_cmd[i]);
		if (!args[i])
			helper_free(args, i, cmd_path);
		i++;
	}
	args[cnt] = NULL;
	return (args);
}

/**
 * Displays error message at fd 2(std err) and exits with code 127
 */
void	msg(char *name, char *msg)
{
	ft_putstr_fd("minihell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(name, 2);
	exit(EXIT_CMD_NOT_FOUND);
}

/**
 * Executes the given command from the given path, handling errors appropriately.
 * 
 * Todo: if child: exec there, if not child process: complete bellow
 */
void	exec_command(t_env_list *env_list, char **splitted_cmd)
{
	char	*cmd_path;
	char	**args;
	char	**env;
	int		i;

	if (!splitted_cmd[0] || splitted_cmd[0][0] == '\0')
	{
		ft_putendl_fd("pipex: permission denied:", 2);
		exit(127);
	}
	cmd_path = get_command_path(env_list, splitted_cmd[0]);
	if (!cmd_path)
	{
		msg(splitted_cmd[0], ": command not found ");
		free_t_env(env_list);
		free_arr(splitted_cmd);
		exit(EXIT_CMD_NOT_FOUND);
	}
	i = 0;
	while (splitted_cmd[i])
		i++;
	args = prepare_command_args(cmd_path, splitted_cmd, i);
	if (!args)
	{
		helper_free(args, i, cmd_path);
	}
	env = converted_env(env_list);
	if (!env) // todo: to handle later
	{
		perror("Failed to convert environment variables.");
		free_args(args, i);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	printf("I am pid %d (parent: %d)\n", getpid(), getppid());

	execve(cmd_path, args, env);
	printf("I am pid %d (after execve parent: %d)\n", getpid(), getppid());

	perror("execve failed");
	free_args(args, i);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

int	fork_and_exec_no_pipes(t_env_list *env_list, char **splitted_cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork failed");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		exec_command(env_list, splitted_cmd);
	}
	waitpid(pid, &status, 0); 
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}

