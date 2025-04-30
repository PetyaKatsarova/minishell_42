#include "../../../includes/parsing.h"

int	get_num_pipes(t_tree *tree)
{
	return (tree->num_pipes);
}

/* returns a t_node pointer to the node storing information about the first command,
** in the order of the input.
*/

t_node	*go_first_cmd(t_tree *tree)
{
	t_node	*current;

	current = go_first_pipe(tree);
	if (current == NULL)
	{
		current = tree->root;
	}
	if (current != NULL && current->token_type == TOKEN_PIPE)
	{
		current = current->producer;
	}
	return (current);
}

/* go_next_cmd returns a t_node pointer to the next command in the order of the input.
** only call when current points to a command node!
** do not call when current points to a pipe node, a redir node, or anywhere else.
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

/* go_next_redir returns a t_node pointer to the next redir in the order of the input.
** only call when current points to a command node or a redir node.
*/

t_node *go_next_redir(t_node *current)
{
	return (current->redirects);
}