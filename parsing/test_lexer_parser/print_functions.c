#include "../parsing.h"

static const char *token_strings[] = {	"TOKEN_NULL",
										"TOKEN_PIPE",
										"TOKEN_INPUT_REDIRECT",
										"TOKEN_OUTPUT_REDIRECT",
										"TOKEN_HEREDOC",
										"TOKEN_APPEND_OUTPUT_REDIRECT",
										"TOKEN_ECHO",
										"TOKEN_CD",
										"TOKEN_PWD",
										"TOKEN_EXPORT",
										"TOKEN_UNSET",
										"TOKEN_ENV",
										"TOKEN_EXIT",
										"TOKEN_WORD"};

void	printlist(t_token *token_list)
{
	t_token *curr = token_list;
	printf("\nOUTPUT LEXER: LINKED LIST:\n");
	while (curr)
	{
		printf("\n    %s: %s\n", token_strings[curr->token_type], curr->lexeme);
		curr = curr->next;
	}
	printf("\n");
}

void	print_token_type(e_token token_type)
{
	printf("token type: %s\n", token_strings[token_type]);
}

void	print_state(e_state state)
{
	char	*state_strings[] = {"OUTSIDE",
								"INSIDE_SINGLES",
								"INSIDE_DOUBLES"};
	printf("state: %s\n", state_strings[state]);
}

void	print_argv(t_node *node)
{

	int 	i = 0;
	bool	first = true;
	printf("argv: ");
	while (node->argv[i] != NULL)
	{
		if (!first)
			printf(", ");
		printf("%s", node->argv[i]);
		first = false;
		i++;
	}
	printf("\n");
}