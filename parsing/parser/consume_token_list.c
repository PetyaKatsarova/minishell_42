#include "../minishell.h"

void	consume_token_list(t_tree *tree)
{
	t_token	*token;
	t_node	*node;

	token = tree->token_list;
	node = go_first_cmd(tree);
	while (token != NULL)
	{
		printf("consume_token_list: ");
		print_token_type(token->token_type);
		
		printf("node token type: ");
		assert(token != NULL);
		assert(node != NULL);
		print_token_type(node->token_type);
		if (token->token_type == TOKEN_PIPE)
		{
			node = go_next_cmd(node);
		}
		token = token->next;
	}
}