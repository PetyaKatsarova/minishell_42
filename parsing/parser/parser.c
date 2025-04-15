#include "../minishell.h"

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
	//printf("countpipes(): num_pipes: %d\n", num_pipes);
	return (num_pipes);
}

static void	makepipes(t_tree *tree)
{
	t_node	*current;
	int		i;
	
	tree->root = nodenew(TOKEN_PIPE, "|", NULL);
	current = tree->root;
	i = 1;
	printf("\nmade new pipe: %d\n", i);
	while (i < tree->num_pipes)
	{
		current->producer = nodenew(TOKEN_PIPE, "|", current);
		current = current->producer;
		i++;
		printf("made new pipe: %d\n", i);
	}
}

void	parser(t_tree *tree, t_token *token_list)
{
	tree->num_pipes = countpipes(token_list);
	if (tree->num_pipes > 0)
	{
		makepipes(tree);
	}

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