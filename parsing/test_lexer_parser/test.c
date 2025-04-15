#include "../minishell.h"

int main(void)
{
	char	*input;
	t_token	*token_list;

	input = readline("> ");
	token_list = NULL;

	printf("\ninput: %s\n", input);

	if (check_quotes(input) == -1)
	{
		printf("ERROR: open quotes\n");
		return (0);
	}

	lexer(&token_list, input);

	printlist(token_list);

	t_tree	*tree;

	tree = treenew(token_list);

	parser(tree, token_list);

	free_list(&token_list);
	free(input);
	printf("\n");
	return (0);
}