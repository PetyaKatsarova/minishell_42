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

static bool	is_empty_var(t_node **node, char *lexeme, int i)
{
	if (**((*node)->argv + i) == '\0')
	{
		if (*lexeme == '$' && is_valid_var_char(*(lexeme + 1)))
		{
			return (true);
		}
	}
	return (false);
}

static void	add_redir_node(t_token **token,
	t_node **node,
	t_parsing_data *data,
	t_node **tail)
{
	if ((*node)->redirects == NULL)
	{
		(*node)->redirects = nodenew((*token)->token_type, NULL, data);
		*tail = (*node)->redirects;
	}
	else
	{
		(*tail)->redirects = nodenew((*token)->token_type, NULL, data);
		*tail = (*tail)->redirects;
	}
	if ((*tail)->token_type == HEREDOC)
	{
		(*tail)->heredoc_str = parse_heredoc((*token)->next->lexeme, data);
	}
	else
	{
		(*tail)->redir_path = parse_lexeme((*token)->next->lexeme, data);
	}
	*token = (*token)->next->next;
}

static void	parse_tokens(t_token **token, t_node **node, t_parsing_data *data)
{
	t_node	*tail;
	int		i;

	i = 0;
	(*node)->argv = make_argv(*token, data);
	while (g_signum != SIGINT && *token != NULL && (*token)->token_type != PIPE)
	{
		if (is_redir((*token)->token_type) == true)
		{
			add_redir_node(token, node, data, &tail);
		}
		else
		{
			*((*node)->argv + i) = parse_lexeme((*token)->lexeme, data);
			if (is_empty_var(node, (*token)->lexeme, i) == true)
			{
				free(*((*node)->argv + i));
				*((*node)->argv + i) = NULL;
			}
			else
				i++;
			(*node)->token_type = (*token)->token_type;
			*token = (*token)->next;
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
	while (g_signum != SIGINT && token != NULL)
	{
		if (token->token_type == PIPE)
		{
			node = go_next_cmd(node);
			token = token->next;
		}
		else
		{
			parse_tokens(&token, &node, data);
			if (*(node->argv) != NULL)
			{
				if (node->token_type == WORD)
				{
					node->token_type = get_type(*(node->argv + 0));
				}
			}
		}
	}
}
