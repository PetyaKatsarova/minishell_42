/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_commands.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 11:38:02 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/18 17:36:33 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Returns exit_status if builtin was found and func executed and 1 or none zero inf command is not built in
It's normal for readline() to leave things in memory to speed up future calls or due to lazy cleanup.
*/
int	handle_commands(t_env_list *env_struct, t_tree *tree, t_node *cmd_node)
{
	int		exit_status;

	exit_status = 0;
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
	{
		//if (exec_on_path(env_struct, cmd_node->argv, get_num_pipes(t_tree *tree)) == EXIT_FAILURE)
		//	return (EXIT_FAILURE);
	}
	env_struct->last_exit_status = exit_status;
	return (exit_status); // 0
}
