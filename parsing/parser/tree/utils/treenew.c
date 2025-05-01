/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   treenew.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:16:28 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:16:29 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include "../../../../includes/parsing.h"

t_tree	*treenew(t_token *token_list, t_env_list *env_list, char *input)
{
	t_tree	*new_tree;

	new_tree = malloc(sizeof(t_tree));
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
