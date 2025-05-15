/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_on_path_helper.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 16:05:50 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/15 16:06:36 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	another_execpath_helper(int pid, t_node *curr_cmd, t_env_list *env_list)
{
	if (pid == 0)
	{
		if (setup_signals_default() == -1
			|| apply_redirections(curr_cmd, -1) != EXIT_SUCCESS)
			free_exit(env_list);
		exec_command(env_list, curr_cmd);
	}
}
