#include "../minishell.h"

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
	//printf("current set to tree->root\n");
	while (	current->token_type == TOKEN_PIPE
			&& current->producer != NULL
			&& current->producer->token_type == TOKEN_PIPE)
	{
		current = current->producer;
	}
	//printf("went down one pipe\n");
	return (current);
}

t_node	*go_next_pipe(t_node *current)
{
	printf("entered go_next_pipe\n");
	while (current->token_type != TOKEN_PIPE)
	{
		printf("looping go_next_pipe\n");
		current = current->parent;
	}
	printf("after loop in go_next_pipe\n");
	current = current->parent;
	printf("returning from go_next_pipe\n");
	return (current);
}