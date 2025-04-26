#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

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
	char	*str_exit_status;//void		check_if_size_reached(char **cpy, char **str, size_t *size);
	char	*orig;

	str_exit_status = ft_itoa(exit_status);
	orig = str_exit_status;
	if (str_exit_status != NULL)
	{
		while (*str_exit_status)
		{
			copy_char(cpy, str, &str_exit_status, size);
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
			copy_char(cpy, str, &var_val, size);
		}
	}
	(*input)++;
	while (is_valid_var_char(**input))
	{
		(*input)++;
	}
}
