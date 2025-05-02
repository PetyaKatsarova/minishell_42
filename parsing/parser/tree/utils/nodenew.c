/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   nodenew.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:16:17 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:16:19 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include "../../../../includes/parsing.h"

t_node	*nodenew(e_token token_type, t_node *parent, t_parsing_data *data)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
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
	new_node->heredoc_str = NULL;
	return (new_node);
}
