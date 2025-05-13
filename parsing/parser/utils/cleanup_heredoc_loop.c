/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   cleanup_heredoc_loop.c                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/13 17:34:01 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/13 17:34:03 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	cleanup_heredoc_loop(int *cpy_stdin, t_parsing_data *data, char **input)
{
	if (g_signum == SIGINT)
	{
		errno = 0;
		if (dup2(*cpy_stdin, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(*cpy_stdin);
			exit_failure_parser(data);
		}
	}
	if (g_signum != SIGINT && *input == NULL)
	{
		write(1, "warning: heredoc delimited by EOF\n", 34);
	}
	if (setup_sigint_prompt() == -1)
	{
		exit_failure_parser(data);
	}
	close(*cpy_stdin);
	free(*input);
	input = NULL;
}
