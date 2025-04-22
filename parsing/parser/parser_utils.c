#include "../../includes/parsing.h"

bool	is_redir(e_token token_type)
{
	if (token_type >= TOKEN_INPUT_REDIRECT
		&& token_type <= TOKEN_APPEND_OUTPUT_REDIRECT)
		{
			return (true);
		}
	return (false);
}