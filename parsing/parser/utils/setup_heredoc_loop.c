/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   setup_heredoc_loop.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/13 17:35:24 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/13 17:35:26 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"
#include "../../../includes/signals.h"

void	setup_heredoc_loop(int *cpy_stdin, t_parsing_data *data, char **cpy_new)
{
	*cpy_stdin = dup(STDIN_FILENO);
	if (*cpy_stdin == -1)
	{
		perror("dup");
		exit_failure_parser(data);
	}
	*cpy_new = data->new;
	if (setup_sigint_heredoc() == -1)
	{
		exit_failure_parser(data);
	}
}
