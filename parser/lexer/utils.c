
#include "../minishell.h"

bool	isendword(char c)
{
	if (c == ' ' || c == '\'' || c == '\"' || c == '\0')
	{
		return (true);
	}
	return (false);
}

int	getwordlen(char *input)
{
	char	*cpy;

	cpy = input;
	while (isendword(*cpy) == false)
	{
		cpy++;
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