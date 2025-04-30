#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static void	populate_data(	t_parsing_data *data,
							int exit_status,
							t_tree *tree,
							t_env_list *env_list)
{
	data->exit_status = exit_status;
	data->size = 1024;
	data->env_list = env_list;
	data->tree = tree;
}

void	parser(char *input, int exit_status, t_tree *tree, t_env_list *env_list)
{
	t_parsing_data	data;
	
	populate_data(&data, exit_status, tree, env_list);
	data.input = input;
	make_pipe_nodes(&data);
	make_cmd_nodes(&data);
	consume_token_list(&data);
}