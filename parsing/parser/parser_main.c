#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

void	parser(char *input, int exit_status, t_tree *tree, t_env_list *env_list)
{
	t_parsing_data	data;
	
	data.input = input;
	data.exit_status = exit_status;
	data.size = 8;
	data.env_list = env_list;
	data.tree = tree;
	make_pipe_nodes(&data);
	make_cmd_nodes(&data);
	consume_token_list(&data);
}