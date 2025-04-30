

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

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
		copy_char(cpy, &cpy_exit_status_str, data);
	}
	(*lexeme) += 2;
	free(exit_status_str);
}
