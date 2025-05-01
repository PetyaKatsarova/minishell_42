/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   consume_special_delim.c                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:11:40 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:11:41 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_token	*consume_special_delim(t_token *tail, char **cpy)
{
	if (**cpy == '|')
		return ((*cpy)++, tokennew(tail, NULL, PIPE));
	if (**cpy == '>')
	{
		(*cpy)++;
		if (**cpy == '>')
		{
			(*cpy)++;
			return (tokennew(tail, NULL, APP_OUT_REDIR));
		}
		return (tokennew(tail, NULL, OUTPUT_REDIR));
	}
	if (**cpy == '<')
	{
		(*cpy)++;
		if (**cpy == '<')
			return ((*cpy)++, tokennew(tail, NULL, HEREDOC));
		return (tokennew(tail, NULL, INPUT_REDIR));
	}
	return (NULL);
}
