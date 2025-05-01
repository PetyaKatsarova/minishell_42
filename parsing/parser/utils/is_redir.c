/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   is_redir.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:18:17 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:18:19 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

bool	is_redir(e_token token_type)
{
	if (token_type >= TOKEN_INPUT_REDIRECT
		&& token_type <= TOKEN_APPEND_OUTPUT_REDIRECT)
	{
		return (true);
	}
	return (false);
}
