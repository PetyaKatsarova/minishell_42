#include "../parsing.h"

static int	count_tokens(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL && token->token_type != TOKEN_PIPE)
	{
		token = token->next;
		count++;
	}
	return (count);
}

static char	**make_argv(t_token *token)
{
	int		count;
	char	**argv;

	count = count_tokens(token);
	argv = malloc((count + 1) * sizeof(char *));
	if (argv == NULL)
	{
		return (NULL); // add error handling: free all
	}
	return (argv);
}

static void	parse_tokens(t_token **token, t_node **node)
{
	int	i;

	i = 0;
	(*node)->argv = make_argv(*token);
	while (*token != NULL && (*token)->token_type != TOKEN_PIPE)
	{
		if ((*node)->token_type == TOKEN_NULL)
		{
			(*node)->token_type = (*token)->token_type;
		}
		(*node)->argv[i] = (*token)->lexeme;
		*token = (*token)->next;
		i++;
	}
	(*node)->argv[i] = NULL;
}

void	consume_token_list(t_tree *tree)
{
	t_token	*token;
	t_node	*node;

	token = tree->token_list;
	node = go_first_cmd(tree);
	while (token != NULL)
	{
		if (token->token_type == TOKEN_PIPE)
		{
			node = go_next_cmd(node);
			token = token->next;
		}
		else
		{
			parse_tokens(&token, &node);
		}
	}
}
