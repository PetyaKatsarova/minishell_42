#include "../../includes/parsing.h"

int	get_num_pipes(t_tree *tree)
{
	return (tree->num_pipes);
}

t_node	*go_first_cmd(t_tree *tree)
{
	t_node	*current;

	current = go_first_pipe(tree);
	if (current == NULL)
	{
		current = tree->root;
	}
	if (current->token_type == TOKEN_PIPE)
	{
		current = current->producer;
	}
	return (current);
}

/* go_next_cmd returns a pointer to the next command in the order of the input.
** only call when current points to a command.
*/

t_node *go_next_cmd(t_node *current)
{
	if (current->parent == NULL)					// this evaluates to true if there is only one cmd and no pipes
	{
		return (NULL);
	}
	else if (current->parent->producer == current)	// this evaluates to true if the current cmd is the producer of the first pipe
	{
		current = current->parent->consumer;
	}
	else if (current->parent->parent == NULL)		// this evaluates to true if the current cmd is the consumer of the last pipe
	{
		return (NULL);
	}
	else											// this will be executed if the current cmd is the consumer of any pipe that is not the last pipe
	{
		current = current->parent->parent->consumer;
	}
	return (current);
}