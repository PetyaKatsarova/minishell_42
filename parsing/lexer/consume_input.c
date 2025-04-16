#include "../minishell.h"

static int	my_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static int	gettype(char *str)
{
	if (my_strcmp(str, "echo") == 0)
		return (TOKEN_ECHO);
	if (my_strcmp(str, "cd") == 0)
		return (TOKEN_CD);
	if (my_strcmp(str, "pwd") == 0)
		return (TOKEN_PWD);
	if (my_strcmp(str, "export") == 0)
		return (TOKEN_EXPORT);
	if (my_strcmp(str, "unset") == 0)
		return (TOKEN_UNSET);
	if (my_strcmp(str, "env") == 0)
		return (TOKEN_ENV);
	if (my_strcmp(str, "exit") == 0)
		return (TOKEN_EXIT);
	return (TOKEN_WORD);
}

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
	new_token = tokennew(tail, lexeme, gettype(lexeme));
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
			return ((*input)++, tokennew(tail, NULL, TOKEN_APPEND_OUTPUT_REDIRECT));
		return (tokennew(tail, NULL, TOKEN_OUTPUT_REDIRECT));
	}
	return (NULL);
}