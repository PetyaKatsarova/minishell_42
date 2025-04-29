#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

/**
 * manipulates tree: make_pipe_nodes, make_cmd_nodes, consume_token_list
 */
void	parser(t_tree *tree, t_env_list *env_list)
{
	make_pipe_nodes(tree);
	make_cmd_nodes(tree);
	consume_token_list(tree, env_list);
}