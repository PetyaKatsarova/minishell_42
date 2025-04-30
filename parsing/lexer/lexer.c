#include "../../includes/parsing.h"

static void	exit_failure(t_token **head, char *input)
{
	free_list(head);
	free(input);
	clear_history();
	exit(EXIT_FAILURE);
}

void	lexer(t_token **head, char *input)
{
	t_token *tail;
	bool	first;
	char	*cpy;

	tail = NULL;
	first = true;
	cpy = input;
	while (*cpy != '\0')
	{
		while (is_whitespace(*cpy) == true)
		{
			cpy++;
		}
		if (is_special_delim(*cpy) == true)
		{
			tail = consume_special_delim(tail, &cpy);
			if (tail == NULL)
			{
				exit_failure(head, input);
			}
		}
		else if (*cpy != '\0')
		{
			tail = consume_chars(tail, &cpy);
			if (tail == NULL)
			{
				exit_failure(head, input);
			}
		}
		if (first == true)
		{
			*head = tail;
			first = false;
		}
	}
}
