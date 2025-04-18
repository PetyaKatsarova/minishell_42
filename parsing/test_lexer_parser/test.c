#include "../parsing.h"

int main(void)
{
	char	*input;
	t_token	*token_list;
	t_tree	*tree;

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

	tree = treenew(token_list);

	parser(tree);

	print_cmd_nodes(tree);

	// free_list(&token_list);
	free_tree(tree);
	free(input);
	printf("\n");
	return (0);
}