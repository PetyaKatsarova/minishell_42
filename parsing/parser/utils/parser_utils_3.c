
#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

void	copy_char(char **target, char **source)
{
	**target = **source;
	(*target)++;
	(*source)++;
}

char	*allocate_str(size_t len, t_parsing_data *data)
{
	char	*str;

	str = malloc((len + 1) * sizeof(char));
	//(void)len;
	//str = NULL;
	if (str == NULL)
	{
		exit_failure_parser(data);
	}
	return (str);
}

static char	*get_variable(char *lexeme, t_parsing_data *data)
{
	size_t	i;
	size_t	j;
	char	*var;

	i = 1;
	while (is_valid_var_char(lexeme[i]))
	{
		i++;
	}
	var = allocate_str(i - 1, data);
	i = 1;
	j = 0;
	while (is_valid_var_char(lexeme[i]))
	{
		var[j++] = lexeme[i++];
	}
	var[j] = '\0';
	return (var);
}

void	expand_variable(char **cpy, char **lexeme, t_parsing_data *data)
{
	char	*var;
	char	*var_val;

	var = get_variable(*lexeme, data);
	var_val = get_env_value(data->env_list, var);
	while (var_val != NULL && *var_val != '\0')
	{
		copy_char(cpy, &var_val);
	}
	(*lexeme)++;
	while (is_valid_var_char(**lexeme))
	{
		(*lexeme)++;
	}
	free(var);
}

void	expand_exit_status(char **cpy, char **lexeme, t_parsing_data *data)
{
	char	*exit_status_str;
	char	*cpy_exit_status_str;

	exit_status_str = ft_itoa(data->exit_status);
	//exit_status_str = NULL;
	if (exit_status_str == NULL)
	{
		exit_failure_parser(data);
	}
	cpy_exit_status_str = exit_status_str;
	while (*cpy_exit_status_str != '\0')
	{
		copy_char(cpy, &cpy_exit_status_str);
	}
	(*lexeme) += 2;
	free(exit_status_str);
}