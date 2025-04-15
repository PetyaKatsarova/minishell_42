#include "../minishell.h"

void	printlist(t_token *token_list)
{
	char *token_strings[] = {"TOKEN_PIPE", "TOKEN_VAR", "TOKEN_EXIT_STATUS", "TOKEN_INPUT_REDIRECT", "TOKEN_OUTPUT_REDIRECT", "TOKEN_HEREDOC", "TOKEN_APPEND_OUTPUT_REDIRECT", "TOKEN_ECHO", "TOKEN_CD", "TOKEN_PWD", "TOKEN_EXPORT", "TOKEN_UNSET", "TOKEN_ENV", "TOKEN_EXIT", "TOKEN_WORD", "TOKEN_SQ_STR", "TOKEN_DQ_STR"};
	t_token *curr = token_list;
	printf("\nOUTPUT LEXER: LINKED LIST:\n");
	while (curr)
	{
		printf("\n    %s: %s\n", token_strings[curr->token_type], curr->lexeme);
		curr = curr->next;
	}
}

void	print_token_type(enum e_token token_type)
{
	char *token_strings[] = {"TOKEN_PIPE", "TOKEN_VAR", "TOKEN_EXIT_STATUS", "TOKEN_INPUT_REDIRECT", "TOKEN_OUTPUT_REDIRECT", "TOKEN_HEREDOC", "TOKEN_APPEND_OUTPUT_REDIRECT", "TOKEN_ECHO", "TOKEN_CD", "TOKEN_PWD", "TOKEN_EXPORT", "TOKEN_UNSET", "TOKEN_ENV", "TOKEN_EXIT", "TOKEN_WORD", "TOKEN_SQ_STR", "TOKEN_DQ_STR"};
	printf("token type: %s\n", token_strings[token_type]);
}