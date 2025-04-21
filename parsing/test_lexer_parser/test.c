#include "../parsing.h"

int main(void)
{
	char	*input;
	t_token	*token_list;

	input = readline("> ");
	token_list = NULL;

	printf("\ninput: %s\n", input);

	if (prelim_syn_check(input) < 0)
	{
		return (0);
	}

	lexer(&token_list, input);

	printlist(token_list);

	t_tree	*tree;

	tree = treenew(token_list);

	if (parser(tree) < 0)
	{
		return (0);
	}

	print_cmd_nodes(tree);

	free_tree(tree);
	//free_list(&token_list);
	free(input);
	printf("\n");
	return (0);
}