#include "../../includes/parsing.h"

static char	*make_str(size_t size)
{
	char	*str;
	char	*cpy;

	str = malloc((size) * sizeof(char));
	if (str == NULL)
	{
		return (NULL); // implement error check: free all
	}
	cpy = str;
	while (size > 0)
	{
		*cpy = '\0';
		cpy++;
		size--;
	}
	return (str);
}

char	*realloc_str(size_t *size, char *str)
{
	char	*orig;
	char	*new;
	char	*cpy;

	*size = *size * 2;
	new = malloc((*size) * sizeof(char));
	if (new == NULL)
	{
		return (NULL); // implement error check: free all
	}
	cpy = new;
	orig = str;
	while (*str)
	{
		*cpy = *str;
		cpy++;
		str++;
	}
	while (cpy < (new + *size))
	{
		*cpy = '\0';
		cpy++;
	}
	free(orig);
	printf("reallocated\n");
	return (new);
}

static void	copy_char(char **cpy, char **str, char **input, size_t *size)
{
	**cpy = **input;
	(*cpy)++;
	(*input)++;
	if ((size_t)(*cpy - *str) >= *size - 1)
	{
		*str = realloc_str(size, *str);
		*cpy = *str;
		while (**cpy != '\0')
		{
			(*cpy)++;
		}
	}
}

static void	expand(char **cpy, char **input, char **str, size_t *size, int exit_status, t_env_list *env_list)
{
	if (*(*input + 1) == '?')
	{
		expand_exit_status(cpy, input, str, size, exit_status);
	}
	else
	{
		expand_var(cpy, input, str, size, env_list);
	}
}

static void	copy_sq(char **cpy, char **input, char **str, size_t *size)
{
	copy_char(cpy, str, input, size);
	while (**input != '\'')
	{
		copy_char(cpy, str, input, size);
	}
	copy_char(cpy, str, input, size);
}

static void	copy_dq(char **cpy, char **input, char **str, size_t *size, t_env_list *env_list, int exit_status)
{
	copy_char(cpy, str, input, size);
	while (**input != '\"')
	{
		if (**input == '$')
			expand(cpy, input, str, size, exit_status, env_list);
		else
			copy_char(cpy, str, input, size);
	}
	copy_char(cpy, str, input, size);
}

static char	*expand_vars(char *input, t_env_list *env_list, int exit_status)
{
	char	*str;
	char	*cpy;
	size_t	size;

	size = 1024;
	str = make_str(size);
	cpy = str;
	while (*input)
	{
		if (*input == '\'')
			copy_sq(&cpy, &input, &str, &size);
		else if (*input == '\"')
			copy_dq(&cpy, &input, &str, &size, env_list, exit_status);
		else if (*input == '$')
			expand(&cpy, &input, &str, &size, exit_status, env_list);
		else
			copy_char(&cpy, &str, &input, &size);
	}
	*cpy = '\0';
	return (str);
}

void	lexer(t_token **head, char *input, t_env_list *env_list, int exit_status)
{
	t_token *tail;
	bool	first;
	char	*str;
	char	*cpy;

	tail = NULL;
	first = true;
	str = expand_vars(input, env_list, exit_status);
	cpy = str;
	while (*cpy != '\0')
	{
		while (is_whitespace(*cpy) == true)
		{
			cpy++;
		}
		if (is_special_delim(*cpy) == true)
		{
			tail = consume_special_delim(tail, &cpy);
		}
		else if (*cpy != '\0')
		{
			tail = consume_chars(tail, &cpy);
		}
		if (first == true)
		{
			*head = tail;
			first = false;
		}
	}
	free(str);
}
