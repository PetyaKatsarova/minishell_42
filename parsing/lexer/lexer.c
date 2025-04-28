#include "../../includes/parsing.h"

void	lexer(t_token **head, char *input, t_env_list *env_list, int exit_status)
{
	t_token *tail;
	bool	first;
	char	*str;
	char	*cpy;

	tail = NULL;
	first = true;
	str = expand_vars(input, env_list, exit_status);
	cpy = str;
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
	free(str);
}
