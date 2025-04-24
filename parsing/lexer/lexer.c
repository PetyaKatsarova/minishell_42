#include "../../includes/parsing.h"

static char	*make_str(int len)
{
	char	*str;

	str = malloc((len) * sizeof(char));
	if (str == NULL)
	{
		return (NULL); // implement error check: free all
	}
	return (str);
}

static void	copy_sq(char **cpy, char **input)
{
	**cpy = **input;
	(*cpy)++;
	(*input)++;
	while (**input != '\'')
	{
		**cpy = **input;
		(*cpy)++;
		(*input)++;
	}
	**cpy = **input;
	(*cpy)++;
	(*input)++;
}

static char	*expand_vars(char *input, t_env_list *env_list, int exit_status)
{
	char	*str;
	char	*cpy;

	str = make_str(131072);
	cpy = str;
	while (*input)
	{
		if (*input == '\'')
			copy_sq(&cpy, &input);
		else if (*input == '$')
		{
			if (*(input + 1) == '?')
				expand_exit_status(&cpy, &input, exit_status);
			else
				expand_var(&cpy, &input, env_list);
		}
		else
		{
			*cpy = *input;
			cpy++;
			input++;
		}
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
