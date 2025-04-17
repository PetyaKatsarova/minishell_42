#include "../parsing.h"

t_token	*tokennew(t_token *tail, char *lexeme, e_token token_type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
	{
		return (NULL); // add error handling: free all
	}
	new_token->lexeme = lexeme;
	new_token->token_type = token_type;
	new_token->next = NULL;
	if (tail != NULL)
	{
		tail->next = new_token;
	}
	return (new_token);
}

void	free_list(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = *head;
	while (current != NULL)
	{
		if (current->lexeme != NULL)
		{
			free(current->lexeme);
		}
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}