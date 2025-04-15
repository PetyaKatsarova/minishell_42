#include "../minishell.h"

void	lexer(t_token **head, char *input)
{
	t_token *tail;

	tail = NULL;
	while (*input != '\0')
	{
		if (tail == NULL)
		{
			if (*input == '\'')
			{
				tail = sq_str(NULL, &input);
			}
			else if (*input == '\"')
			{
				tail = dq_str(NULL, &input);
			}
			else if (*input == 32)
			{
				input++;
			}
			else
			{
				tail = outside_quotes(NULL, &input);
			}
			*head = tail;
		}
		else
		{
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
		}
	}
}
