#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static bool	is_valid_var_char(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= 'a' && c <= 'z')
		return (true);
	if (c == '_')
		return (true);
	return (false);
}

static char	*allocate_str(size_t len)
{
	char	*str;

	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
	{
		return (NULL); // implement error check: free all
	}
	return (str);
}

static char	*get_variable(char *lexeme)
{
	size_t	i;
	size_t	j;
	char	*var;

	i = 1;
	while (is_valid_var_char(lexeme[i]))
	{
		i++;
	}
	var = allocate_str(i - 1);
	i = 1;
	j = 0;
	while (is_valid_var_char(lexeme[i]))
	{
		var[j++] = lexeme[i++];
	}
	var[j] = '\0';
	return (var);
}

static void	expand_variable(char **cpy, char **lexeme, t_env_list *env_list)
{
	char	*var;
	char	*var_val;

	var = get_variable(*lexeme);
	var_val = get_env_value(env_list, var);
	(*lexeme)++;
	while (var_val != NULL && *var_val != '\0')
	{
		**cpy = *var_val;
		(*cpy)++;
		var_val++;
	}
	while (is_valid_var_char(**lexeme))
	{
		(*lexeme)++;
	}
	free(var);
}

static void	expand(char **cpy, char **lexeme, t_env_list *env_list)
{
	expand_variable(cpy, lexeme, env_list);
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
			expand_variable(cpy, lexeme, env_list);
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
			expand(&cpy, &lexeme, env_list);
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
	char	*str;

	str = allocate_str(1024);
	str = populate_str(str, lexeme, env_list);
	return (str);
}