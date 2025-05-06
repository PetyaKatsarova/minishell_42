/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   utils.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:13:34 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:13:36 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

bool	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
	{
		return (true);
	}
	return (false);
}

bool	is_special_delim(char c)
{
	if (c == '|')
	{
		return (true);
	}
	if (c == '>' || c == '<')
	{
		return (true);
	}
	return (false);
}

bool	isendword(t_state state, char c)
{
	if (state == OUTSIDE)
	{
		if (is_whitespace(c) == true)
		{
			return (true);
		}
		if (is_special_delim(c) == true)
		{
			return (true);
		}
		if (c == '\0')
		{
			return (true);
		}
	}
	return (false);
}

int	getwordlen(char *input)
{
	char	*cpy;
	t_state	state;

	cpy = input;
	state = OUTSIDE;
	state = set_state(state, *cpy);
	while (isendword(state, *cpy) == false)
	{
		cpy++;
		state = set_state(state, *cpy);
	}
	return (cpy - input);
}

int	set_state(t_state state, char c)
{
	if (state == OUTSIDE)
	{
		if (c == '\'')
			state = INSIDE_SINGLES;
		else if (c == '\"')
			state = INSIDE_DOUBLES;
	}
	else if (state == INSIDE_SINGLES)
	{
		if (c == '\'')
			state = OUTSIDE;
	}
	else if (state == INSIDE_DOUBLES)
	{
		if (c == '\"')
			state = OUTSIDE;
	}
	return (state);
}
