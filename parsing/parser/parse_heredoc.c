
#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static int	my_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	//printf("input: %s\n", s1);
	//printf("delim: %s\n", s2);
	//printf("%d\n", *s1 - *s2);
	return (*s1 - *s2);
}

static void	heredoc_loop(char *delim, t_parsing_data *data)
{
	char	*input;
	char	*cpy_new;
	char	*cpy_input;

	input = readline("> ");
	cpy_new = data->new;
	while (my_strcmp(input, delim) != 0)
	{
		while (*cpy_new != '\0')
		{
			cpy_new++;
		}
		cpy_input = input;
		while (*cpy_input != '\0')
		{
			*cpy_new = *cpy_input;
			cpy_new++;
			cpy_input++;
		}
		*cpy_new = '\n';
		free(input);
		input = NULL;
		input = readline("> ");
	}
	free(input);
}

char	*parse_heredoc(char *lexeme, t_parsing_data *data)
{
	char	*delim;
	
	data->new = allocate_str(data);
	if (data->new == NULL)
	{
		exit_failure_parser(data);
	}
	delim = lexeme;
	heredoc_loop(delim, data);
	return (data->new);
}