#include "../../includes/parsing.h"

void	parser(t_tree *tree)
{
	make_pipe_nodes(tree);

	//printf("parser(): made pipes\n");

	make_cmd_nodes(tree);

	//printf("parser(): made cmd nodes\n");

	consume_token_list(tree);

	//printf("parser(): consumed token list\n");
}