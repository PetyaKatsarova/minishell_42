#include "../../includes/parsing.h"

t_node	*nodenew(e_token token_type, t_node *parent)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
	{
		return (NULL); // add error handling: free all
	}
	new_node->parent = parent;
	new_node->token_type = token_type;
	new_node->argv = NULL;
	new_node->producer = NULL;
	new_node->consumer = NULL;
	new_node->redirects = NULL;
	new_node->redir_path = NULL;
	return (new_node);
}

t_tree	*treenew(t_token *token_list, int exit_status)
{
	t_tree	*new_tree;

	new_tree = malloc(sizeof(t_tree));
	if (new_tree == NULL)
	{
		return (NULL); // add error handling: free all
	}
	new_tree->exit_status = exit_status;
	new_tree->num_pipes = 0;
	new_tree->token_list = token_list;
	new_tree->root = NULL;
	return (new_tree);
}

static int	countpipes(t_token *current)
{
	int	num_pipes;

	num_pipes = 0;
	while (current != NULL)
	{
		if (current->token_type == TOKEN_PIPE)
		{
			num_pipes++;
		}
		current = current->next;
	}
	return (num_pipes);
}

void	make_pipe_nodes(t_tree *tree)
{
	t_node	*current;
	int		i;

	tree->num_pipes = countpipes(tree->token_list);
	i = 0;
	while (i < tree->num_pipes)
	{
		if (i == 0)
		{
			tree->root = nodenew(TOKEN_PIPE, NULL);
			current = tree->root;
		}
		else
		{
			current->producer = nodenew(TOKEN_PIPE, current);
			current = current->producer;
		}
		i++;
	}
}

void	make_cmd_nodes(t_tree *tree)
{
	t_node	*current;

	current = go_first_pipe(tree);
	if (current == NULL)
	{
		tree->root = nodenew(TOKEN_NULL, NULL);
		return ;
	}
	current->producer = nodenew(TOKEN_NULL, current);
	while (current != NULL)
	{
		current->consumer = nodenew(TOKEN_NULL, current);
		current = go_next_pipe(current);
	}
}