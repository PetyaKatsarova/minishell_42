
#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

char	*allocate_str(t_parsing_data *data)
{
	char	*str;
	char	*cpy;
	size_t	i;

	str = malloc((data->size) * sizeof(char));
	if (str == NULL)
	{
		exit_failure_parser(data);
	}
	cpy = str;
	i = 0;
	while (i < data->size)
	{
		*cpy = '\0';
		cpy++;
		i++;
	}
	return (str);
}
