#include "../../../includes/parsing.h"

/* this will return a pointer to the first pipe, the first pipe is the lowest pipe in the tree.
** if there are no pipes the function returns a NULL pointer.
*/

t_node	*go_first_pipe(t_tree *tree)
{
	t_node *current;

	if (tree->root == NULL || tree->root->token_type != TOKEN_PIPE)
	{
		return (NULL);
	}
	current = tree->root;
	while (current->token_type == TOKEN_PIPE
			&& current->producer != NULL
			&& current->producer->token_type == TOKEN_PIPE)
	{
		current = current->producer;
	}
	return (current);
}

t_node	*go_next_pipe(t_node *current)
{
	while (current->token_type != TOKEN_PIPE)
	{
		current = current->parent;
	}
	current = current->parent;
	return (current);
}