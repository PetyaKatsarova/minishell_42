
#include "../../../../includes/minishell.h"
#include "../../../../includes/parsing.h"

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
