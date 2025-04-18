#include "../parsing.h"

static void	free_pipes(t_tree *tree)
{
	t_node	*node;
	t_node	*next_pipe;

	node = go_first_pipe(tree);
	while (node != NULL)
	{
		next_pipe = go_next_pipe(node);
		free(node);
		node = next_pipe;
	}
}

static void	free_cmds(t_tree *tree)
{
	t_node	*node;
	t_node	*next_cmd;
	//int		i;

	node = go_first_cmd(tree);
	while (node != NULL)
	{
		// i = 0;
		// while (node->argv[i] != NULL)
		// {
		// 	free(node->argv[i]);
		// 	node->argv[i] = NULL;
		// 	i++;
		// }
		free(node->argv);
		next_cmd = go_next_cmd(node);
		free(node);
		node = next_cmd;
	}
}

void	free_tree(t_tree *tree)
{
	free_cmds(tree);
	free_pipes(tree);
	free_list(&tree->token_list);
	free(tree);
}