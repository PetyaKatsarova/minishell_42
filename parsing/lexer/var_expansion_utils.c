
#include "../../includes/parsing.h"

char	*alloc_str(size_t size)
{
	char	*str;
	char	*cpy;

	str = malloc((size) * sizeof(char));
	if (str == NULL)
	{
		return (NULL); // implement error check: free all
	}
	cpy = str;
	while (size > 0)
	{
		*cpy = '\0';
		cpy++;
		size--;
	}
	return (str);
}

char	*realloc_str(size_t *size, char *str)
{
	char	*orig;
	char	*new;
	char	*cpy;

	*size = *size * 2;
	new = alloc_str(*size);
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

void	copy_char(char **cpy, char **str, char **input, size_t *size)
{
	**cpy = **input;
	(*cpy)++;
	(*input)++;
	if ((size_t)(*cpy - *str) >= *size - 1)
	{
		*str = realloc_str(size, *str);
		*cpy = *str;
		while (**cpy != '\0')
		{
			(*cpy)++;
		}
	}
}

bool	is_valid_var_char(char c)
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
