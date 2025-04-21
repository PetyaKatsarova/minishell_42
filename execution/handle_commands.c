/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_commands.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 11:38:02 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/21 17:22:24 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * If builtin executes and returns exit status, else returns -1
 */
int execute_builtin(t_node *cmd_node, t_tree *tree, t_env_list *env_struct)
{
	if (cmd_node->token_type == TOKEN_EXIT)
		return do_exit(env_struct, tree, cmd_node);
	else if (cmd_node->token_type == TOKEN_PWD)
		return get_pwd();
	else if (cmd_node->token_type == TOKEN_CD)
		return do_cd(cmd_node->argv, env_struct);
	else if (cmd_node->token_type == TOKEN_ENV)
		return get_env(env_struct);
	else if (cmd_node->token_type == TOKEN_ECHO)
		return do_echo(cmd_node->argv);
	else if (cmd_node->token_type == TOKEN_EXPORT)
		return do_export(cmd_node->argv, env_struct);
	else if (cmd_node->token_type == TOKEN_UNSET)
		return do_unset(cmd_node->argv, env_struct);
	return (EXIT_NO_EXECUTABLE);
}

/**
 * 	
 */

// int	handle_command(t_env_list *env_struct, t_tree *tree, t_node *curr_cmd)
// {
// 	int 	num_pipes;
//	int 	status;
	
//	status = -1;
//	num_pipes = get_num_pipes(tree);
//	curr_cmd = go_first_cmd(tree);
//	if (num_pipes == 0 || go_next_cmd(curr_cmd) == NULL)
//	{
//		status = execute_builtin(curr_cmd, tree, env_struct);
//		env_struct->last_exit_status = status;
//	}
//	if (status == -1)
//	{
//		if (num_pipes > 0)
//		   exec_pipeline(env_struct, tree);
//		else
//		   exec_on_path(env_struct, curr_cmd, 0);
//	}
//	return (status);
// }
 
