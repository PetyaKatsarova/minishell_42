#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static int	get_len_sq(char **lexeme)
{
	int	len;

	len = 0;
	(*lexeme)++;
	while (**lexeme != '\'')
	{
		(*lexeme)++;
		len++;
	}
	(*lexeme)++;
	return (len);
}

static int	get_len_dq(char **lexeme)
{
	int	len;

	len = 0;
	(*lexeme)++;
	while (**lexeme != '\"')
	{
		(*lexeme)++;
		len++;
	}
	(*lexeme)++;
	return (len);
}

static int	get_len(char *lexeme, t_env_list *env_list)
{
	char	*var_val;
	int		len;

	len = 0;
	while (*lexeme)
	{
		if (*lexeme == '\'')
		{
			len += get_len_sq(&lexeme);
		}
		else if (*lexeme == '\"')
		{
			len += get_len_dq(&lexeme);
		}
		else if (*lexeme == '$')
		{
			len += get_len_var(&lexeme);
		}
		else
		{
			len++;
			lexeme++;
		}
	}
	return (len);
}

static char	*make_str(int len)
{
	char	*str;

	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
	{
		return (NULL); // implement error check: free all
	}
	return (str);
}

static char	*populate_str(char *str, char *lexeme)
{
	char	*var_val;
	char	*cpy;
	e_state	state;

	cpy = str;
	state = OUTSIDE;
	while (*lexeme)
	{
		state = set_state(state, *lexeme);
		if (state == OUTSIDE)
		{
			if (*lexeme != '\'' && *lexeme != '\"')
			{
				*cpy = *lexeme;
				cpy++;
			}
		}
		else
		{
			*cpy = *lexeme;
			cpy++;
		}
		lexeme++;
	}
	*cpy = '\0';
	return (str);
}

char *parse_lexeme(char *lexeme, t_env_list *env_list)
{
	int		len;
	char	*str;

	len = get_len(lexeme, env_list);
	//printf("parse_lexeme: len: %d\n", len);
	str = make_str(len);
	//str = populate_str(str, lexeme);
	return (str);
}