/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_commands.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 16:01:12 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/10 13:40:46 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_builtin(t_node *cmd_node, t_tree *tree, t_env_list *env_struct)
{
	if (cmd_node->token_type == EXIT)
		return (do_exit(env_struct, tree, cmd_node));
	else if (cmd_node->token_type == PWD)
		return (get_pwd(cmd_node->argv));
	else if (cmd_node->token_type == CD)
		return (do_cd(cmd_node->argv, env_struct));
	else if (cmd_node->token_type == ENV)
		return (get_env(cmd_node->argv, env_struct));
	else if (cmd_node->token_type == ECHO)
		return (do_echo(cmd_node->argv));
	else if (cmd_node->token_type == EXPORT)
		return (do_export(cmd_node->argv, env_struct));
	else if (cmd_node->token_type == UNSET)
		return (do_unset(cmd_node->argv, env_struct));
	return (EXIT_CMD_NOT_FOUND);
}

static bool	is_redir_builtin(t_node *cmd_node)
{
	return (cmd_node->token_type == ECHO
		|| cmd_node->token_type == PWD
		|| cmd_node->token_type == ENV);
}

static int	handle_no_cmd_redir(t_node *redir, t_node *cmd_node, int status)
{
	pid_t	pid;

	if (redir && cmd_node->token_type == TOKEN_NULL)
	{
		pid = fork();
		if (pid == 0)
			exit(apply_redirections(cmd_node));
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (status);
}

static int	execute_non_word(t_env_list *env, t_tree *tree,
	t_node *cmd_node, t_node *redir)
{
	pid_t	pid;
	int		status;

	status = handle_no_cmd_redir(redir, cmd_node, 0);
	if (redir && is_redir_builtin(cmd_node))
	{
		pid = fork();
		if (pid == 0)
		{
			if (apply_redirections(cmd_node) != EXIT_SUCCESS)
				exit(EXIT_FAILURE);
			exit(execute_builtin(cmd_node, tree, env));
		}
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (execute_builtin(cmd_node, tree, env));
}

int	handle_single_command(t_env_list *env, t_tree *tree, t_node *cmd_node)
{
	t_node	*redir;

	redir = go_next_redir(cmd_node);
	if (cmd_node->token_type != WORD)
		return (execute_non_word(env, tree, cmd_node, redir));
	return (exec_on_path(env, cmd_node, 0));
}
