#include "../parsing.h"

void	lexer(t_token **head, char *input)
{
	t_token *tail;
	bool	first;

	tail = NULL;
	first = true;
	while (*input != '\0')
	{
		while (is_whitespace(*input) == true)
		{
			input++;
		}
		if (is_special_delim(*input) == true)
		{
			tail = consume_special_delim(tail, &input);
		}
		else
		{
			tail = consume_chars(tail, &input);
		}
		if (first == true)
		{
			*head = tail;
			first = false;
		}
	}
}
