
#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

char	*reallocate_str(char *str, t_parsing_data *data)
{
	char	*orig;
	char	*new;
	char	*cpy;

	data->size = data->size * 2;
	new = allocate_str(data);
	cpy = new;
	orig = str;
	while (*str)
	{
		*cpy = *str;
		cpy++;
		str++;
	}
	free(orig);
	return (new);
}
