#include "../../includes/parsing.h"

int	syn_check(t_tree *tree)
{
	t_token	*current;
	bool	redir_flag;

	current = tree->token_list;
	redir_flag = false;
	while (current != NULL)
	{
		if (redir_flag == true)
		{
			if (is_redir(current->token_type))
				return (write(1, "syntax error: unexpected redir\n", 32), -1);
			else if (current->token_type == TOKEN_PIPE)
				return (write(1, "syntax error: unexpected '|'\n", 30), -1);
			else
				redir_flag = false;
		}
		if (is_redir(current->token_type) == true)
			redir_flag = true;
		current = current->next;
	}
	if (redir_flag == true)
		return (write(1, "syntax error: unexpected end of line\n", 37), -1);
	return (0);
}