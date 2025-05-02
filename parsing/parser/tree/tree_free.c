/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   tree_free.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:14:49 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:14:51 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static void	free_pipes(t_tree *tree)
{
	t_node	*node;
	t_node	*next_pipe;

	node = go_first_pipe(tree);
	while (node != NULL)
	{
		next_pipe = go_next_pipe(node);
		free(node);
		node = next_pipe;
	}
}

static void	free_redirs(t_node *node)
{
	t_node	*next;

	while (node != NULL)
	{
		next = node->redirects;
		free(node->redir_path);
		free(node->heredoc_str);
		free(node);
		node = next;
	}
}

static void	free_argv(t_node *node)
{
	int	i;

	i = 0;
	while (node->argv[i] != NULL)
	{
		free(node->argv[i]);
		i++;
	}
	free(node->argv);
}

static void	free_cmds(t_tree *tree)
{
	t_node	*node;
	t_node	*next_cmd;

	node = go_first_cmd(tree);
	while (node != NULL)
	{
		if (node->argv != NULL)
			free_argv(node);
		free_redirs(node->redirects);
		next_cmd = go_next_cmd(node);
		if (node->parent != NULL)
		{
			if (node->parent->producer == node)
				node->parent->producer = NULL;
			else
				node->parent->consumer = NULL;
		}
		if (node->parent == NULL)
			tree->root = NULL;
		free(node);
		node = next_cmd;
	}
}

void	free_tree(t_tree *tree)
{
	free_cmds(tree);
	free_pipes(tree);
	free_list(&tree->token_list);
	free(tree);
}
