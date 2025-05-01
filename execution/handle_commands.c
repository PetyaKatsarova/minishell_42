/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_commands.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 11:38:02 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/30 20:32:10 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Some builtins must affect the parent shell
cd, exit, export, unset — these modify the shell’s state (env, directory, exit).
If run in a child, their effects are discarded once the child exits.
 */

/**
 * If builtin executes and returns exit status, else returns -1
 */
int execute_builtin(t_node *cmd_node, t_tree *tree, t_env_list *env_struct)
{
	if (cmd_node->token_type == EXIT)
		return do_exit(env_struct, tree, cmd_node);
	else if (cmd_node->token_type == PWD)
		return get_pwd(cmd_node->argv);
	else if (cmd_node->token_type == CD)
		return do_cd(cmd_node->argv, env_struct);
	else if (cmd_node->token_type == ENV)
		return get_env(cmd_node->argv, env_struct);
	else if (cmd_node->token_type == ECHO)
		return do_echo(cmd_node->argv);
	else if (cmd_node->token_type == EXPORT)
		return do_export(cmd_node->argv, env_struct);
	else if (cmd_node->token_type == UNSET)
		return do_unset(cmd_node->argv, env_struct);
	return (EXIT_CMD_NOT_FOUND);
}

/**
 * Check if cmd is: echo, pwd, env: can work with redirects, others not
 */
static bool is_redir_builtin(t_node *cmd_node)
{
	return (cmd_node->token_type == ECHO || cmd_node->token_type == PWD ||
		cmd_node->token_type == ENV);
}

int	handle_single_command(t_env_list *env_struct, t_tree *tree, t_node *cmd_node)
{
	int		status = 0;
	pid_t	pid;
	t_node	*redir = go_next_redir(cmd_node);

	if (cmd_node->token_type != WORD) // builtin
	{
		if (redir && is_redir_builtin(cmd_node))
		{
			pid = fork();
			if (pid == 0)
			{
				if (apply_redirections(cmd_node) != EXIT_SUCCESS)
					exit(EXIT_FAILURE);
				exit(execute_builtin(cmd_node, tree, env_struct));
			}
			waitpid(pid, &status, 0);
			return WEXITSTATUS(status);
		}
		else //if (is_redir_builtin(cmd_node) || !redir)
			return execute_builtin(cmd_node, tree, env_struct);
		// else
		// {
		// 	write(STDERR_FILENO, "Redirection not supported for this builtin\n", 44);
		// 	return EXIT_FAILURE;
		// }
	}
	else
		return exec_on_path(env_struct, cmd_node, 0); // redirection done there
}


