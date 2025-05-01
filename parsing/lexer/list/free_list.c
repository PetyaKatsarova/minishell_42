
#include "../../../includes/parsing.h"

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
