#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

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
		exit_failure_parser(data);
	}
	populate_new(lexeme, data);
	return (data->new);
}