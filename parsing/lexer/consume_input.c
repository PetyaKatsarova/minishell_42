#include "../../includes/parsing.h"

t_token	*consume_chars(t_token *tail, char **cpy)
{	
	t_token *new_token;
	char	*lexeme;
	char	*cpy_lexeme;
	e_state	state;

	lexeme = malloc((getwordlen(*cpy) + 1) * sizeof(char));
	if (lexeme == NULL)
	{
		return (NULL);
	}
	cpy_lexeme = lexeme;
	state = set_state(OUTSIDE, **cpy);
	while (isendword(state, **cpy) == false)
	{
		*cpy_lexeme = **cpy;
		(*cpy)++;
		cpy_lexeme++;
		state = set_state(state, **cpy);
	}
	*cpy_lexeme = '\0';
	new_token = tokennew(tail, lexeme, TOKEN_WORD);
	if (new_token == NULL)
	{
		free(lexeme);
		return (NULL);
	}
	return (new_token);
}

t_token *consume_special_delim(t_token *tail, char **cpy)
{
	if (**cpy == '|')
		return ((*cpy)++, tokennew(tail, NULL, TOKEN_PIPE));
	if (**cpy == '>')
	{
		(*cpy)++;
		if (**cpy == '>')
			return ((*cpy)++, tokennew(tail, NULL, TOKEN_APPEND_OUTPUT_REDIRECT));
		return (tokennew(tail, NULL, TOKEN_OUTPUT_REDIRECT));
	}
	if (**cpy == '<')
	{
		(*cpy)++;
		if (**cpy == '<')
			return ((*cpy)++, tokennew(tail, NULL, TOKEN_HEREDOC));
		return (tokennew(tail, NULL, TOKEN_INPUT_REDIRECT));
	}
	return (NULL);
}