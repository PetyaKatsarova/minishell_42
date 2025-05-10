/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   consume_chars.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:11:19 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:11:27 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/signals.h"

t_token	*consume_chars(t_token *tail, char **cpy)
{
	t_token	*new_token;
	char	*lexeme;
	char	*cpy_lexeme;
	t_state	state;

	lexeme = malloc((getwordlen(*cpy) + 1) * sizeof(char));
	if (lexeme == NULL)
		return (NULL);
	cpy_lexeme = lexeme;
	state = set_state(OUTSIDE, **cpy);
	while (g_signum == 0 && isendword(state, **cpy) == false)
	{
		*cpy_lexeme = **cpy;
		(*cpy)++;
		cpy_lexeme++;
		state = set_state(state, **cpy);
	}
	*cpy_lexeme = '\0';
	new_token = tokennew(tail, lexeme, WORD);
	if (new_token == NULL)
		return (free(lexeme), NULL);
	return (new_token);
}
