/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   lexer_main.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:11:54 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:11:55 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static void	process_char(	char **cpy,
							t_token **tail,
							t_token **head,
							char *input)
{
	while (is_whitespace(**cpy) == true)
	{
		(*cpy)++;
	}
	if (is_special_delim(**cpy) == true)
	{
		*tail = consume_special_delim(*tail, cpy);
		if (*tail == NULL)
		{
			perror("lexer_main.c: malloc failed");
			exit_failure_lexer(head, input);
		}
	}
	else if (**cpy != '\0')
	{
		*tail = consume_chars(*tail, cpy);
		if (*tail == NULL)
		{
			perror("lexer_main.c: malloc failed");
			exit_failure_lexer(head, input);
		}
	}
}

void	lexer(t_token **head, char *input)
{
	t_token	*tail;
	bool	first;
	char	*cpy;

	tail = NULL;
	first = true;
	cpy = input;
	while (*cpy != '\0')
	{
		process_char(&cpy, &tail, head, input);
		if (first == true)
		{
			*head = tail;
			first = false;
		}
	}
}
