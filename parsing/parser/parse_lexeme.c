#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static char	*allocate_str(int len)
{
	char	*str;

	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
	{
		return (NULL); // implement error check: free all
	}
	return (str);
}

static void	parse_sq(char **cpy, char **lexeme)
{
	(*lexeme)++;
	while (**lexeme != '\'')
	{
		**cpy = **lexeme;
		(*cpy)++;
		(*lexeme)++;
	}
	(*lexeme)++;
}

static void	parse_dq(char **cpy, char **lexeme)
{
	(*lexeme)++;
	while (**lexeme != '\"')
	{
		{
			**cpy = **lexeme;
			(*cpy)++;
			(*lexeme)++;
		}
	}
	(*lexeme)++;
}

static char	*populate_str(char *str, char *lexeme)
{
	char	*cpy;
	
	cpy = str;
	while (*lexeme)
	{
		if (*lexeme == '\'')
		{
			parse_sq(&cpy, &lexeme);
		}
		else if (*lexeme == '\"')
		{
			parse_dq(&cpy, &lexeme);
		}
		else
		{
			*cpy = *lexeme;
			cpy++;
			lexeme++;
		}
	}
	*cpy = '\0';
	return (str);
}

char *parse_lexeme(char *lexeme)
{
	char	*str;

	str = allocate_str(ft_strlen(lexeme));
	str = populate_str(str, lexeme);
	return (str);
}