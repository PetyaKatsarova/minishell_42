
#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

void	exit_failure_parser(t_parsing_data *data)
{
	clear_history();
	free_t_env(data->env_list);
	free_tree(data->tree);
	free(data->input);
	exit(EXIT_FAILURE);
}
