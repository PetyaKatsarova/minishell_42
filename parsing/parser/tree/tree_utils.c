#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

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

t_tree	*treenew(t_token *token_list, t_env_list *env_list, char *input)
{
	t_tree	*new_tree;

	new_tree = malloc(sizeof(t_tree));
	//new_tree = NULL;
	if (new_tree == NULL)
	{
		clear_history();
		free_t_env(env_list);
		free_list(&token_list);
		free(input);
		exit(EXIT_FAILURE);
	}
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

void	make_pipe_nodes(t_parsing_data *data)
{
	t_node	*current;
	int		i;

	data->tree->num_pipes = countpipes(data->tree->token_list);
	i = 0;
	while (i < data->tree->num_pipes)
	{
		if (i == 0)
		{
			data->tree->root = nodenew(TOKEN_PIPE, NULL, data);
			current = data->tree->root;
		}
		else
		{
			current->producer = nodenew(TOKEN_PIPE, current, data);
			current = current->producer;
		}
		i++;
	}
}

void	make_cmd_nodes(t_parsing_data *data)
{
	t_node	*current;

	current = go_first_pipe(data->tree);
	if (current == NULL)
	{
		data->tree->root = nodenew(TOKEN_NULL, NULL, data);
		return ;
	}
	current->producer = nodenew(TOKEN_NULL, current, data);
	while (current != NULL)
	{
		current->consumer = nodenew(TOKEN_NULL, current, data);
		current = go_next_pipe(current);
	}
}