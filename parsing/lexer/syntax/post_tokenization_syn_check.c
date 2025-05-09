/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   syn_check.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:12:54 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:13:02 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"
#include "../../../includes/minishell.h"

static int	error_check(t_token *current, t_env_list *env_list, bool *redir)
{
	if (is_redir(current->token_type))
	{
		env_list->last_exit_status = 2;
		write(2, "syntax error: unexpected redir\n", 32);
		return (2);
	}
	else if (current->token_type == PIPE)
	{
		env_list->last_exit_status = 2;
		write(2, "syntax error: unexpected '|'\n", 30);
		return (2);
	}
	else
	{
		*redir = false;
	}
	return (0);
}

int	post_tokenization_syn_check(t_token *current, t_env_list *env_list)
{
	bool	redir;

	redir = false;
	while (current != NULL)
	{
		if (redir == true)
		{
			if (error_check(current, env_list, &redir) == 2)
			{
				return (2);
			}
		}
		if (is_redir(current->token_type) == true)
		{
			redir = true;
		}
		current = current->next;
	}
	if (redir == true)
	{
		env_list->last_exit_status = 2;
		write(2, "syntax error: unexpected end of line\n", 37);
		return (2);
	}
	return (0);
}
