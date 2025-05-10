/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parse_lexeme.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:13:58 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:14:02 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static void	parse_sq(char **cpy, char **lexeme, t_parsing_data *data)
{
	(*lexeme)++;
	while (**lexeme != '\'')
	{
		copy_char(cpy, lexeme, data);
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
			copy_char(cpy, lexeme, data);
		}
	}
	(*lexeme)++;
}

static void	populate_new(char *lexeme, t_parsing_data *data)
{
	char	*cpy;

	cpy = data->new;
	while (g_signum == 0 && *lexeme)
	{
		if (*lexeme == '\'')
		{
			parse_sq(&cpy, &lexeme, data);
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
			copy_char(&cpy, &lexeme, data);
		}
	}
	*cpy = '\0';
}

char	*parse_lexeme(char *lexeme, t_parsing_data *data)
{
	data->new = allocate_str(data);
	populate_new(lexeme, data);
	return (data->new);
}
