
#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

static int	my_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	get_type(char *str)
{
	if (my_strcmp(str, "echo") == 0)
		return (TOKEN_ECHO);
	if (my_strcmp(str, "cd") == 0)
		return (TOKEN_CD);
	if (my_strcmp(str, "pwd") == 0)
		return (TOKEN_PWD);
	if (my_strcmp(str, "export") == 0)
		return (TOKEN_EXPORT);
	if (my_strcmp(str, "unset") == 0)
		return (TOKEN_UNSET);
	if (my_strcmp(str, "env") == 0)
		return (TOKEN_ENV);
	if (my_strcmp(str, "exit") == 0)
		return (TOKEN_EXIT);
	return (TOKEN_WORD);
}