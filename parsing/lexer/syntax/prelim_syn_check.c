/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   prelim_syn_check.c                                  :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:12:42 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:12:44 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"
#include "../../../includes/minishell.h"

static int	check_if_empty(char *input)
{
	if (*input == '\0')
	{
		return (-1);
	}
	return (0);
}

static int	check_if_only_whitespace(char *input)
{
	while (is_whitespace(*input))
	{
		input++;
	}
	if (*input == '\0')
	{
		return (-1);
	}
	return (0);
}

static int	check_pipes(e_state *state, bool *pipe_flag, char input)
{
	if (input == '|')
	{
		if (*pipe_flag == true)
			return (3);
		else
			*pipe_flag = true;
	}
	else if (is_whitespace(input) == false)
		*pipe_flag = false;
	if (input == '\'')
		*state = INSIDE_SINGLES;
	else if (input == '\"')
		*state = INSIDE_DOUBLES;
	return (0);
}

static int	check_quotes(char *input)
{
	e_state	state;
	bool	pipe_flag;

	state = OUTSIDE;
	pipe_flag = true;
	while (*input)
	{
		if (state == OUTSIDE)
		{
			if (check_pipes(&state, &pipe_flag, *input) != 0)
				return (3);
		}
		else if (state == INSIDE_SINGLES && *input == '\'')
			state = OUTSIDE;
		else if (state == INSIDE_DOUBLES && *input == '\"')
			state = OUTSIDE;
		input++;
	}
	if (pipe_flag == true)
		return (3);
	if (state != OUTSIDE)
		return (4);
	return (0);
}

int	prelim_syn_check(char *input, t_env_list *env_list)
{
	int	res;

	if (check_if_empty(input) != 0)
	{
		return (env_list->last_exit_status = 0, 1);
	}
	if (check_if_only_whitespace(input) != 0)
	{
		return (env_list->last_exit_status = 0, 1);
	}
	res = check_quotes(input);
	if (res == 3)
	{
		env_list->last_exit_status = 2;
		write(1, "syntax error: misplaced '|'\n", 28);
		return (2);
	}
	if (res == 4)
	{
		env_list->last_exit_status = 2;
		write(1, "syntax error: open quotes\n", 26);
		return (2);
	}
	return (0);
}
