#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static char	*make_str(int len)
{
	char	*str;
	int		i;

	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
	{
		return (NULL); // implement error check: free all
	}
	i = 0;
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

static void	parse_dq(char **cpy, char **lexeme, t_env_list *env_list)
{
	(*lexeme)++;
	while (**lexeme != '\"')
	{
		if (**lexeme == '$')
		{
			expand_var(cpy, lexeme, env_list);
		}
		else
		{
			**cpy = **lexeme;
			(*cpy)++;
			(*lexeme)++;
		}
	}
	(*lexeme)++;
}

static char	*populate_str(char *str, char *lexeme, t_env_list *env_list)
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
			parse_dq(&cpy, &lexeme, env_list);
		}
		else if (*lexeme == '$')
		{
			expand_var(&cpy, &lexeme, env_list);
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

char *parse_lexeme(char *lexeme, t_env_list *env_list)
{
	int		len;
	char	*str;

	str = make_str(1024);
	str = populate_str(str, lexeme, env_list);
	return (str);
}