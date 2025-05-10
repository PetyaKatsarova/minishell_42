/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser_main.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:14:13 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:14:14 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

void	parser(char *input, t_tree *tree, t_env_list *env_list)
{
	t_parsing_data	data;

	if (g_signum == 0)
	{
		data.input = input;
		data.size = 1024;
		data.env_list = env_list;
		data.tree = tree;
		make_pipe_nodes(&data);
		make_cmd_nodes(&data);
		consume_token_list(&data);
	}
}
