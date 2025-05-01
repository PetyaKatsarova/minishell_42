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

void	exit_failure_lexer(t_token **head, char *input)
{
	free_list(head);
	free(input);
	clear_history();
	exit(EXIT_FAILURE);
}
