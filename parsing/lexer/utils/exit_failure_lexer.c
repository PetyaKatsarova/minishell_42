
#include "../../../includes/parsing.h"

void	exit_failure_lexer(t_token **head, char *input)
{
	free_list(head);
	free(input);
	clear_history();
	exit(EXIT_FAILURE);
}
