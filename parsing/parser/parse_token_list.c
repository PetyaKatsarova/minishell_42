#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static void	add_redir_node(t_token **token, t_node **node, t_parsing_data *data, t_node **tail_redir_node)
{
	if ((*node)->redirects == NULL)
	{
		(*node)->redirects = nodenew((*token)->token_type, NULL, data);
		*tail_redir_node = (*node)->redirects;
	}
	else
	{
		(*tail_redir_node)->redirects = nodenew((*token)->token_type, NULL, data);
		*tail_redir_node = (*tail_redir_node)->redirects;
	}
	(*tail_redir_node)->redir_path = parse_lexeme((*token)->next->lexeme, data);
	*token = (*token)->next->next;
}

static void	parse_tokens(t_token **token, t_node **node, t_parsing_data *data)
{
	t_node	*tail_redir_node;
	int		i;

	i = 0;
	(*node)->argv = make_argv(*token, data);
	while (*token != NULL && (*token)->token_type != TOKEN_PIPE)
	{
		if (is_redir((*token)->token_type) == true)
		{
			add_redir_node(token, node, data, &tail_redir_node);
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
