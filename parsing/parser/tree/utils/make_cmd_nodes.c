/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   make_cmd_nodes.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:15:58 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:16:00 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include "../../../../includes/parsing.h"

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
