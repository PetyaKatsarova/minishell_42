#include "../../../../includes/minishell.h"
#include "../../../../includes/parsing.h"

t_node	*nodenew(e_token token_type, t_node *parent, t_parsing_data *data)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	//new_node = NULL;
	if (new_node == NULL)
	{
		exit_failure_parser(data);
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
