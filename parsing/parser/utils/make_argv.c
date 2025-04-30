
#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

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

char	**make_argv(t_token *token, t_parsing_data *data)
{
	int		count;
	char	**argv;

	count = count_tokens(token);
	argv = malloc((count + 1) * sizeof(char *));
	if (argv == NULL)
	{
		exit_failure_parser(data);
	}
	while (count > 0)
	{
		argv[--count] = NULL;
	}
	return (argv);
}