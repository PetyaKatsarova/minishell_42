#include "../minishell.h"

void	lexer(t_token **head, char *input)
{
	t_token *tail;
	bool	first;

	tail = NULL;
	while (*input != '\0')
	{
		if (tail == NULL)
		{
			first = true;
		}
		if (*input == '\'')
		{
			tail = sq_str(tail, &input);
		}
		else if (*input == '\"')
		{
			tail = dq_str(tail, &input);
		}
		else if (*input == 32)
		{
			input++;
		}
		else
		{
			tail = outside_quotes(tail, &input);
		}
		if (first == true)
		{
			*head = tail;
			first = false;
		}
	}
}
