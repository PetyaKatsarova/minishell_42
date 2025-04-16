#include "../minishell.h"

void	consume_token_list(t_tree *tree)
{
	t_token	*token;

	token = tree->token_list;
	while (token != NULL)
	{
		printf("consume_token_list: ");
		print_token_type(token->token_type);
		token = token->next;

	}
}