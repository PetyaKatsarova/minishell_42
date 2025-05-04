
#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static void	parse_line(char **cpy_new, char **cpy_input, t_parsing_data *data, bool exp)
{
	while (**cpy_input != '\0')
	{
		if (exp == true && **cpy_input == '$')
		{
			expand(cpy_new, cpy_input, data);
		}
		else
		{
			copy_char(cpy_new, cpy_input, data);
		}
	}
	**cpy_new = '\n';
}

static char	*get_input(t_parsing_data *data)
{
	char	*input;
	
	input = readline("> ");
	if (input == NULL)
	{
		write(2, "HEREDOC: input is NULL\n", 23);
		exit_failure_parser(data);
	}
	return (input);
}

static void	heredoc_loop(char *delim, t_parsing_data *data, bool exp)
{
	char	*input;
	char	*cpy_new;
	char	*cpy_input;

	input = get_input(data);
	cpy_new = data->new;
	while (my_strcmp(input, delim) != 0)
	{
		while (*cpy_new != '\0')
		{
			cpy_new++;
		}
		cpy_input = input;
		parse_line(&cpy_new, &cpy_input, data, exp);
		free(input);
		input = get_input(data);
	}
	free(input);
}

static void	extract_delim(char *delim, bool *exp)
{
	if (*delim == '\'' || *delim == '\"')
	{
		*exp = false;
		delim++;
		while (*delim != '\0')
		{
			*(delim - 1) = *delim;
			delim++;
		}
		delim--;
		*delim = '\0';
		delim--;
		*delim = '\0';
	}
	else
	{
		*exp = true;
	}
}

char	*parse_heredoc(char *delim, t_parsing_data *data)
{
	bool	exp;
	
	data->new = allocate_str(data);
	extract_delim(delim, &exp);
	heredoc_loop(delim, data, exp);
	return (data->new);
}