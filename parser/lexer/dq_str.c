#include "../minishell.h"

t_token	*dq_str(t_token *tail, char **input)
{	
	t_token *new_token;
	char	*lexeme;
	char	*cpy_lexeme;

	(*input)++;
	lexeme = malloc((getlen(*input, '\"') + 1) * sizeof(char));
	if (lexeme == NULL)
	{
		return (NULL); // implement error handling: free all
	}
	cpy_lexeme = lexeme;
	while (**input != '\"')
	{
		*cpy_lexeme = **input;
		(*input)++;	
		cpy_lexeme++;
	}
	*cpy_lexeme = '\0';
	(*input)++;
	new_token = tokennew(tail, lexeme, TOKEN_DQ_STR);
	if (new_token == NULL)
	{
		return (NULL); // implement error handling: free all
	}
	return (new_token);
}