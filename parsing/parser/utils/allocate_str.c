
#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

char	*allocate_str(t_parsing_data *data)
{
	char	*str;
	char	*cpy;

	str = malloc((data->size) * sizeof(char));
	if (str == NULL)
	{
		exit_failure_parser(data);
	}
	cpy = str;
	while ((size_t)(cpy - str) < data->size)
	{
		*cpy = '\0';
		cpy++;
	}
	return (str);
}
