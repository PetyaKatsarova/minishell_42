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

static int	get_len_var(char *str)
{
	int	len;
	len = 0;
	str++;
	while (*str != '\0' && is_valid_var_char(*str) == true)
	{
		str++;
		len++;
	}
	return (len);
}

static void	extract_var(char *str, char *var)
{
	str++;
	while (is_valid_var_char(*str))
	{
		*var = *str;
		var++;
		str++;
	}
	*var = '\0';
}

void	expand_exit_status(char **cpy, char **input, char **str, size_t *size, int exit_status)
{
	char	*str_exit_status;
	char	*orig;

	str_exit_status = ft_itoa(exit_status);
	orig = str_exit_status;
	if (str_exit_status != NULL)
	{
		while (*str_exit_status)
		{
			**cpy = *str_exit_status;
			(*cpy)++;
			str_exit_status++;
			check_if_size_reached(cpy, str, size);
		}
	}
	free(orig);
	(*input) += 2;
}

void	expand_var(char **cpy, char **input, char **str, size_t *size, t_env_list *env_list)
{
	char	*var;
	char	*var_val;

	var = malloc((get_len_var(*input) + 1) * sizeof(char));
	// if (var == NULL)
	// {
	// 	free all
	// }
	extract_var(*input, var);
	var_val = get_env_value(env_list, var);
	free(var);
	if (var_val != NULL)
	{
		while (*var_val)
		{
			**cpy = *var_val;
			(*cpy)++;
			var_val++;
			check_if_size_reached(cpy, str, size);
		}
	}
	(*input)++;
	while (is_valid_var_char(**input))
	{
		(*input)++;
	}
}
