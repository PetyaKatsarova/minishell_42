
#include "../../../includes/parsing.h"
#include "../../../includes/minishell.h"

void	expand(char **cpy, char **lexeme, t_parsing_data *data)
{
	if (*(*lexeme + 1) == '?')
	{
		expand_exit_status(cpy, lexeme, data);
	}
	else if (is_valid_var_char(*(*lexeme + 1)) == false)
	{
		copy_char(cpy, lexeme, data);
	}
	else
	{
		expand_variable(cpy, lexeme, data);
	}
}