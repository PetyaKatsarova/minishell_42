#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static int	count_tokens(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL && token->token_type != TOKEN_PIPE)
	{
		if (is_redir(token->token_type))
		{
			token = token->next->next;
		}
		else
		{
			token = token->next;
			count++;
		}
	}
	return (count);
}

static char	**make_argv(t_token *token, t_tree *tree)
{
	int		count;
	char	**argv;

	count = count_tokens(token);
	argv = malloc((count + 1) * sizeof(char *));
	if (argv == NULL)
	{
		free(tree); // call free_all instead
		return (NULL); // add error handling: free all
	}
	return (argv);
}

static int	my_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static int	get_type(char *str)
{
	if (my_strcmp(str, "echo") == 0)
		return (TOKEN_ECHO);
	if (my_strcmp(str, "cd") == 0)
		return (TOKEN_CD);
	if (my_strcmp(str, "pwd") == 0)
		return (TOKEN_PWD);
	if (my_strcmp(str, "export") == 0)
		return (TOKEN_EXPORT);
	if (my_strcmp(str, "unset") == 0)
		return (TOKEN_UNSET);
	if (my_strcmp(str, "env") == 0)
		return (TOKEN_ENV);
	if (my_strcmp(str, "exit") == 0)
		return (TOKEN_EXIT);
	return (TOKEN_WORD);
}

static void	parse_tokens(t_token **token, t_node **node, t_tree *tree, t_env_list *env_list)
{
	int	i;

	i = 0;
	(*node)->argv = make_argv(*token, tree);
	while (*token != NULL && (*token)->token_type != TOKEN_PIPE)
	{
		if (is_redir((*token)->token_type) == true)
		{
			*token = (*token)->next->next;
		}
		else
		{
			*((*node)->argv + i) = parse_lexeme((*token)->lexeme, env_list, tree);
			*token = (*token)->next;
			i++;
		}
	}
	*((*node)->argv + i) = NULL;
}

void	consume_token_list(t_tree *tree, t_env_list *env_list)
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
			parse_tokens(&token, &node, tree, env_list);
			node->token_type = get_type(node->argv[0]);
		}
	}
}
