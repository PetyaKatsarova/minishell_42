
#include "../../includes/parsing.h"

static void	expand(char **cpy, char **input, char **str, size_t *size, int exit_status, t_env_list *env_list)
{
	if (*(*input + 1) == '?')
	{
		expand_exit_status(cpy, input, str, size, exit_status);
	}
	else if (is_valid_var_char(*(*input + 1)) == false)
	{
		copy_char(cpy, str, input, size);
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

char	*expand_vars(char *input, t_env_list *env_list, int exit_status)
{
	char	*str;
	char	*cpy;
	size_t	size;

	size = 1024;
	str = alloc_str(size);
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