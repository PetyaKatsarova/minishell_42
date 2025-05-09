/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   tokennew.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:12:19 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:12:21 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

t_token	*tokennew(t_token *tail, char *lexeme, t_type token_type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
	{
		return (NULL);
	}
	new_token->lexeme = lexeme;
	new_token->token_type = token_type;
	new_token->next = NULL;
	if (tail != NULL)
	{
		tail->next = new_token;
	}
	return (new_token);
}
