
#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

bool	is_redir(e_token token_type)
{
	if (token_type >= TOKEN_INPUT_REDIRECT
		&& token_type <= TOKEN_APPEND_OUTPUT_REDIRECT)
		{
			return (true);
		}
	return (false);
}

void	exit_failure_parser(t_parsing_data *data)
{
	clear_history();
	free_t_env(data->env_list);
	free_tree(data->tree);
	free(data->input);
	exit(EXIT_FAILURE);
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

int	get_type(char *str)
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
