#include "../minishell.h"

void	consume_token_list(t_tree *tree)
{
	t_node	*current;
	t_token	*token;

	current = tree->root;
	token = tree->token_list;
	while (token != NULL)
	{
		if (token->token_type == TOKEN_PIPE)
		{
			current = go_next_pipe(current);
		}
		print_token_type(token->token_type);
		token = token->next;

	}
}