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

static void	copy_char(char **target, char **source)
{
	**target = **source;
	(*target)++;
	(*source)++;
}

static char	*allocate_str(size_t len, t_parsing_data *data)
{
	char	*str;

	str = malloc((len + 1) * sizeof(char));
	//(void)len;
	//str = NULL;
	if (str == NULL)
	{
		clear_history();
		free_t_env(data->env_list);
		free_tree(data->tree);
		free(data->input);
		exit(EXIT_FAILURE);
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

static void	expand_variable(char **cpy, char **lexeme, t_parsing_data *data)
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

static void	expand_exit_status(char **cpy, char **lexeme, t_parsing_data *data)
{
	char	*exit_status_str;
	char	*cpy_exit_status_str;

	exit_status_str = ft_itoa(data->exit_status);
	//exit_status_str = NULL;
	if (exit_status_str == NULL)
	{
		clear_history();
		free_t_env(data->env_list);
		free_tree(data->tree);
		free(data->input);
		exit(EXIT_FAILURE);
	}
	cpy_exit_status_str = exit_status_str;
	while (*cpy_exit_status_str != '\0')
	{
		copy_char(cpy, &cpy_exit_status_str);
	}
	(*lexeme) += 2;
	free(exit_status_str);
}

static void	expand(char **cpy, char **lexeme, t_parsing_data *data)
{
	if (*(*lexeme + 1) == '?')
	{
		expand_exit_status(cpy, lexeme, data);
	}
	else if (is_valid_var_char(*(*lexeme + 1)) == false)
	{
		copy_char(cpy, lexeme);
	}
	else
	{
		expand_variable(cpy, lexeme, data);
	}
}

static void	parse_sq(char **cpy, char **lexeme)
{
	(*lexeme)++;
	while (**lexeme != '\'')
	{
		copy_char(cpy, lexeme);
	}
	(*lexeme)++;
}

static void	parse_dq(char **cpy, char **lexeme, t_parsing_data *data)
{
	(*lexeme)++;
	while (**lexeme != '\"')
	{
		if (**lexeme == '$')
		{
			expand(cpy, lexeme, data);
		}
		else
		{
			copy_char(cpy, lexeme);
		}
	}
	(*lexeme)++;
}

static void	populate_new(char *lexeme, t_parsing_data *data)
{
	char	*cpy;
	
	cpy = data->new;
	while (*lexeme)
	{
		if (*lexeme == '\'')
		{
			parse_sq(&cpy, &lexeme);
		}
		else if (*lexeme == '\"')
		{
			parse_dq(&cpy, &lexeme, data);
		}
		else if (*lexeme == '$')
		{
			expand(&cpy, &lexeme, data);
		}
		else
		{
			copy_char(&cpy, &lexeme);
		}
	}
	*cpy = '\0';
}

char *parse_lexeme(char *lexeme, t_parsing_data *data)
{
	data->new = allocate_str(data->size, data);
	//data->new = NULL;
	if (data->new == NULL)
	{
		clear_history();
		free_t_env(data->env_list);
		free_tree(data->tree);
		free(data->input);
		exit(EXIT_FAILURE);
	}
	populate_new(lexeme, data);
	return (data->new);
}