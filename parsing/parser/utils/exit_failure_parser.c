/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   exit_failure_parser.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:17:21 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:17:24 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

void	exit_failure_parser(t_parsing_data *data)
{
	clear_history();
	free_t_env(data->env_list);
	free_tree(data->tree);
	free(data->input);
	//termios_sigquit_on();
	exit(EXIT_FAILURE);
}
