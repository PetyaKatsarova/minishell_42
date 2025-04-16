
#include "../minishell.h"


bool	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
	{
		return (true);
	}
	return (false);
}

bool	isendword(e_state state, char c)
{
	if (state == OUTSIDE)
	{
		if (is_whitespace(c) == true)
		{
			return (true);
		}
		if (c == '\0')
		{
			return (true);
		}
	}
	return (false);
}

int	getwordlen(char *input)
{
	char	*cpy;
	e_state	state;

	cpy = input;
	state = OUTSIDE;
	state = set_state(state, *cpy);
	while (isendword(state, *cpy) == false)
	{
		cpy++;
		state = set_state(state, *cpy);
		
	}
	return (cpy - input);
}

int	getlen(char *input, char end)
{
	char	*cpy;

	cpy = input;
	while (*cpy != end)
	{
		cpy++;
	}
	return (cpy - input);
}
