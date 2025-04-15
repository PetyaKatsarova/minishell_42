#include "../minishell.h"

int	get_num_pipes(t_tree *tree)
{
	return (tree->num_pipes);
}

t_node	*go_first_cmd(t_tree *tree)
{
	t_node	*current;

	current = go_first_pipe(tree);
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
	if (current->parent->producer == current)
	{
		current = current->parent->consumer;
	}
	else
	{
		current = current->parent->parent->consumer;
	}
	return (current);
}