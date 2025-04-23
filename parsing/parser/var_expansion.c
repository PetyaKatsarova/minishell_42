#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

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

int	get_len_var(char **lexeme)
{
	int	len;
	len = 0;
	(*lexeme)++;
	while (is_valid_var_char(**lexeme) == true)
	{
		(*lexeme)++;
		len++;
	}
	return (len);
}

int	get_len_var_val(char *var, t_env_list *env_list)
{
	char	*val;
	int		len;

	val = get_env_value(env_list, var);
	len = 0;
	while (*val)
	{
		len++;
	}
	return (len);
}