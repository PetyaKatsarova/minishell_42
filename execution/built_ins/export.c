/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 11:41:36 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/02 11:41:36 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_export(char **input_args, t_env_list *env_struct)
{
	t_env_list	*sorted_env;
	int			has_error;

	has_error = 0;
	sorted_env = NULL;
	if (input_args[1])
		process_export_args(input_args, env_struct, &has_error);
	else
	{
		sorted_env = sort_env(env_struct);
		if (!sorted_env)
			err_malloc(NULL, "minishell: sorted env-struct failed");
		print_env_export(sorted_env);
		free_t_env(sorted_env);
	}
	if (has_error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
