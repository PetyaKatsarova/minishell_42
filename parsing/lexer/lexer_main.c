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
#include "../../includes/minishell.h"

static void	process_char(char **cpy, t_token **tail)
{
	while (is_whitespace(**cpy) == true)
	{
		(*cpy)++;
	}
	if (is_special_delim(**cpy) == true)
	{
		*tail = consume_special_delim(*tail, cpy);
	}
	else if (**cpy != '\0')
	{
		*tail = consume_chars(*tail, cpy);
	}
}

void	lexer(t_token **head, char *input, t_env_list *env_list)
{
	t_token	*tail;
	bool	first;
	char	*cpy;

	tail = NULL;
	first = true;
	cpy = input;
	while (g_signum == 0 && *cpy != '\0')
	{
		process_char(&cpy, &tail);
		if (tail == NULL)
		{
			perror("lexer");
			exit_failure_lexer(head, input, env_list);
		}
		if (first == true)
		{
			*head = tail;
			first = false;
		}
	}
}
