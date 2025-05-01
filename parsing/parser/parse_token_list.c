/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parse_token_list.c                                  :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:14:30 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:14:31 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static void	add_redir_node(t_token **token,
	t_node **node,
	t_parsing_data *data,
	t_node **tail_redir)
{
	if ((*node)->redirects == NULL)
	{
		(*node)->redirects = nodenew((*token)->token_type, NULL, data);
		*tail_redir = (*node)->redirects;
	}
	else
	{
		(*tail_redir)->redirects = nodenew((*token)->token_type, NULL, data);
		*tail_redir = (*tail_redir)->redirects;
	}
	(*tail_redir)->redir_path = parse_lexeme((*token)->next->lexeme, data);
	*token = (*token)->next->next;
}

static void	parse_tokens(t_token **token, t_node **node, t_parsing_data *data)
{
	t_node	*tail_redir;
	int		i;

	i = 0;
	(*node)->argv = make_argv(*token, data);
	while (*token != NULL && (*token)->token_type != TOKEN_PIPE)
	{
		if (is_redir((*token)->token_type) == true)
		{
			add_redir_node(token, node, data, &tail_redir);
		}
		else
		{
			*((*node)->argv + i) = parse_lexeme((*token)->lexeme, data);
			(*node)->token_type = (*token)->token_type;
			*token = (*token)->next;
			i++;
		}
	}
	*((*node)->argv + i) = NULL;
}

void	consume_token_list(t_parsing_data *data)
{
	t_token	*token;
	t_node	*node;

	token = data->tree->token_list;
	node = go_first_cmd(data->tree);
	while (token != NULL)
	{
		if (token->token_type == TOKEN_PIPE)
		{
			node = go_next_cmd(node);
			token = token->next;
		}
		else
		{
			parse_tokens(&token, &node, data);
			if (node->token_type == TOKEN_WORD)
			{
				node->token_type = get_type(*(node->argv + 0));
			}
		}
	}
}
