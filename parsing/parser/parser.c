#include "../minishell.h"

void	parser(t_tree *tree)
{
	make_pipe_nodes(tree);

/* 	TEST:
	t_node *current = go_first_pipe(tree);
	print_token_type(current->token_type);
	while (current->token_type == TOKEN_PIPE && current->parent != NULL && current->parent->token_type == TOKEN_PIPE)
	{
		current = go_next_pipe(current);
		print_token_type(current->token_type);
	} */

	consume_token_list(tree);
}