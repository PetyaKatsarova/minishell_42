#include "../minishell.h"

void	free_all(t_token **h, t_tree *r, bool free)
{
	static t_token	*head = NULL;
	static t_tree	*tree = NULL;

	if (head == NULL)
		head = h;
	if (tree == NULL)
		tree = r;
	if (free == true)
	{
		free_list(head);
	}
}