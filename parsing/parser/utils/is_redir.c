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

bool	is_redir(t_type token_type)
{
	if (token_type >= INPUT_REDIR && token_type <= APP_OUT_REDIR)
	{
		return (true);
	}
	return (false);
}
