/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_commands.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 11:38:02 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/28 16:43:47 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * If builtin executes and returns exit status, else returns -1
 */
int execute_builtin(t_node *cmd_node, t_tree *tree, t_env_list *env_struct)
{
	if ((cmd_node->token_type = TOKEN_INPUT_REDIRECT) || (cmd_node->token_type == TOKEN_OUTPUT_REDIRECT) || (cmd_node->token_type == TOKEN_APPEND_OUTPUT_REDIRECT))
		apply_redirections(cmd_node);
	if (cmd_node->token_type == TOKEN_EXIT)
		return do_exit(env_struct, tree, cmd_node);
	else if (cmd_node->token_type == TOKEN_PWD)
		return get_pwd(cmd_node->argv);
	else if (cmd_node->token_type == TOKEN_CD)
		return do_cd(cmd_node->argv, env_struct);
	else if (cmd_node->token_type == TOKEN_ENV)
		return get_env(cmd_node->argv, env_struct);
	else if (cmd_node->token_type == TOKEN_ECHO)
		return do_echo(cmd_node->argv);
	else if (cmd_node->token_type == TOKEN_EXPORT)
		return do_export(cmd_node->argv, env_struct);
	else if (cmd_node->token_type == TOKEN_UNSET)
		return do_unset(cmd_node->argv, env_struct);
	return (EXIT_CMD_NOT_FOUND);
}
