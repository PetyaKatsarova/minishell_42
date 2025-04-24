#include "../../includes/parsing.h"

t_token	*consume_chars(t_token *tail, char **input)
{	
	t_token *new_token;
	char	*lexeme;
	char	*cpy_lexeme;
	e_state	state;

	lexeme = malloc((getwordlen(*input) + 1) * sizeof(char));
	if (lexeme == NULL)
	{
		return (NULL); // implement error handling: free all
	}
	cpy_lexeme = lexeme;
	state = set_state(OUTSIDE, **input);
	while (isendword(state, **input) == false)
	{
		*cpy_lexeme = **input;
		(*input)++;
		cpy_lexeme++;
		state = set_state(state, **input);
	}
	*cpy_lexeme = '\0';
	new_token = tokennew(tail, lexeme, TOKEN_WORD);
	if (new_token == NULL)
	{
		return (NULL); // implement error handling: free all
	}
	return (new_token);
}

t_token *consume_special_delim(t_token *tail, char **input)
{
	if (**input == '|')
		return ((*input)++, tokennew(tail, NULL, TOKEN_PIPE));
	if (**input == '>')
	{
		(*input)++;
		if (**input == '>')
			return ((*input)++, tokennew(tail, NULL, TOKEN_APPEND_OUTPUT_REDIRECT));
		return (tokennew(tail, NULL, TOKEN_OUTPUT_REDIRECT));
	}
	if (**input == '<')
	{
		(*input)++;
		if (**input == '<')
			return ((*input)++, tokennew(tail, NULL, TOKEN_HEREDOC));
		return (tokennew(tail, NULL, TOKEN_INPUT_REDIRECT));
	}
	return (NULL);
}