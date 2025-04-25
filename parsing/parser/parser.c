#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

/**
 * manipulates tree: make_pipe_nodes, make_cmd_nodes, consume_token_list
 */
int	parser(t_tree *tree)
{
	if (syn_check(tree) < 0)
	{
		return (-1);
	}
	make_pipe_nodes(tree);
	make_cmd_nodes(tree);
	consume_token_list(tree);
	return (0);
}