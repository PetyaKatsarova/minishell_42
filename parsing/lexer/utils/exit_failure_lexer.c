/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   exit_failure_lexer.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:13:18 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:13:20 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"
#include "../../../includes/minishell.h"

void	exit_failure_lexer(t_token **head, char *input, t_env_list *env_list)
{
	free_list(head);
	free(input);
	free_t_env(env_list);
	clear_history();
	//termios_sigquit_on();
	exit(EXIT_FAILURE);
}
