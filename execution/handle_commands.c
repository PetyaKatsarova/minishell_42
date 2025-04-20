/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_commands.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 11:38:02 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/20 21:19:38 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool is_builtin(t_node *cmd_node)
{
	return ((cmd_node->token_type == TOKEN_EXIT || cmd_node->token_type == TOKEN_CD
		|| cmd_node->token_type == TOKEN_ECHO || cmd_node->token_type == TOKEN_PWD
		|| cmd_node->token_type == TOKEN_ENV || cmd_node->token_type == TOKEN_EXPORT
		|| cmd_node->token_type == TOKEN_UNSET));
}

static int	execute_builtin(t_node *cmd_node, t_tree *tree, t_env_list *env_struct)
{
	int	exit_status;

	if (cmd_node->token_type == TOKEN_EXIT)
		return do_exit(env_struct, tree, cmd_node);
	else if (cmd_node->token_type == TOKEN_PWD)
		exit_status = get_pwd();
	else if (cmd_node->token_type == TOKEN_CD)
		exit_status = do_cd(cmd_node->argv, env_struct);
	else if (cmd_node->token_type == TOKEN_ENV)
		exit_status = get_env(env_struct);
	else if (cmd_node->token_type == TOKEN_ECHO)
		exit_status = do_echo(cmd_node->argv);
	else if (cmd_node->token_type == TOKEN_EXPORT)
		exit_status = do_export(cmd_node->argv, env_struct);
	else if (cmd_node->token_type == TOKEN_UNSET)
		exit_status = do_unset(cmd_node->argv, env_struct);
	else
		exit_status = 0; // todo??
	return (exit_status);
}

/*
Returns exit_status if builtin was found and func executed and 1 or none zero inf command is not built in
It's normal for readline() to leave things in memory to speed up future calls or due to lazy cleanup.
*/
// int	handle_commands(t_env_list *env_struct, t_tree *tree, t_node *cmd_node, int is_pipe)
// {
// 	int		exit_status;
// 	bool	is_builtin_cmd;

// 	exit_status = 0;
// 	is_builtin_cmd = is_builtin(cmd_node);
// 	if (is_builtin_cmd)
// 		exit_status = execute_builtin(cmd_node, tree, env_struct);
// 	else
// 	{
// 		exit_status = exec_on_path(env_struct, cmd_node, is_pipe);
// 		env_struct->last_exit_status = exit_status;
// 		return (exit_status);
// 	}
// 	env_struct->last_exit_status = exit_status;
// 	return (exit_status);
// }
// int			exec_on_path(t_env_list *env_list, t_node	*curr_cmd, int is_pipe);

static void setup_child_io(int prev_fd, int pipe_fd[2], bool has_next)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (has_next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

static void execute_child(t_env_list *env, t_tree *tree, t_node *cmd, int prev_fd, int pipe_fd[2], bool has_next)
{
	(void) tree;
	setup_child_io(prev_fd, pipe_fd, has_next);
	if (!is_builtin(cmd))
		exec_on_path(env, cmd, 1);
	exit(1); // if execve fails
}

static int execute_pipeline(t_env_list *env, t_tree *tree, t_node *cmd_node)
{
	int pipe_fd[2];
	int prev_fd = -1;
	pid_t pid;
	int status = 0;
	t_node *cmd = cmd_node;

	while (cmd)
	{
		bool has_next = cmd->consumer != NULL;
		if (has_next && pipe(pipe_fd) == -1)
			perror("pipe");

		pid = fork();
		if (pid == -1)
			perror("fork");

		if (pid == 0)
			execute_child(env, tree, cmd, prev_fd, pipe_fd, has_next);

		if (prev_fd != -1)
			close(prev_fd);
		if (has_next)
			close(pipe_fd[1]);
		prev_fd = has_next ? pipe_fd[0] : -1;
		cmd = cmd->consumer;
	}

	while (wait(&status) > 0)
		;
	env->last_exit_status = WEXITSTATUS(status);
	return (env->last_exit_status);
}

// testing: todo: remove
// t_node *get_last_cmd(t_node *cmd_node)
// {
// 	t_node *cpy = cmd_node;
// 	while (cpy && go_next_cmd(cpy))
// 		cpy = go_next_cmd(cpy);
// 	return cpy; // This is the last node before NULL
// }


int handle_commands(t_env_list *env, t_tree *tree, t_node *cmd_node)
{
	if (!cmd_node)
		return (0);
	// if builtin and not last child: execute builtin, otherwise, continue
	if (is_builtin(cmd_node) && (go_next_cmd(cmd_node) == NULL ||get_num_pipes(tree) == 0))
	{
		env->last_exit_status = execute_builtin(cmd_node, tree, env);
		return (env->last_exit_status);
	}
	else
		return execute_pipeline(env, tree, cmd_node);
}
