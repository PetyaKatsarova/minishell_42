#include "../minishell.h"

void	lexer(t_token **head, char *input)
{
	t_token *tail;
	bool	first;

	tail = NULL;
	first = true;
	while (*input != '\0')
	{
		if (is_whitespace(*input) == true)
		{
			input++;
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
