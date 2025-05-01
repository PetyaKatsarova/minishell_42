/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_functions_2.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:51:26 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:51:27 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	print_node(t_node *node)
{
	printf("\n");
	printf("parent: %p\n", node->parent);
	printf("token_type: ");
	print_token_type(node->token_type);
	print_argv(node);
	printf("producer: %p\n", node->producer);
	printf("consumer: %p\n", node->consumer);
	printf("redirects: %p\n", node->redirects);
	printf("redir_path: %s\n", node->redir_path);
	printf("\n");
}

void	print_cmd_nodes(t_tree *tree)
{
	t_node	*current;
	t_node	*redir;
	int		count;

	current = go_first_cmd(tree);
	count = 1;
	while (current != NULL)
	{
		printf("CMD %d", count);
		print_node(current);
		redir = go_next_redir(current);
		if (redir != NULL)
		{
			printf("REDIRECTIONS:\n");
		}
		while (redir != NULL)
		{
			print_node(redir);
			redir = go_next_redir(redir);
		}
		current = go_next_cmd(current);
		count++;
	}
}

void	print_cmd_node_readable(t_node *node)
{
	printf("\n");
	printf("token_type: ");
	print_token_type(node->token_type);
	print_argv(node);
	printf("\n");
}

void	print_redir_node(t_node *node)
{
	printf("     token_type: ");
	print_token_type(node->token_type);
	printf("     redir_path: %s\n", node->redir_path);
	printf("\n");
}

void	print_cmd_nodes_readable(t_tree *tree)
{
	t_node	*current;
	t_node	*redir;
	int		count;

	current = go_first_cmd(tree);
	count = 1;
	while (current != NULL)
	{
		printf("CMD %d", count);
		print_cmd_node_readable(current);
		redir = go_next_redir(current);
		if (redir != NULL)
		{
			printf("     REDIRECTIONS CMD %d:\n", count);
		}
		while (redir != NULL)
		{
			print_redir_node(redir);
			redir = go_next_redir(redir);
		}
		current = go_next_cmd(current);
		count++;
	}
}
