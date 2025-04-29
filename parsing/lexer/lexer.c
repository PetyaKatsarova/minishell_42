#include "../../includes/parsing.h"

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
		}
		else if (*cpy != '\0')
		{
			tail = consume_chars(tail, &cpy);
		}
		if (first == true)
		{
			*head = tail;
			first = false;
		}
	}
}
