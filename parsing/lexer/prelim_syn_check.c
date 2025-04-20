
#include "../../includes/parsing.h"

/*
** this function uses the logic of a state machine. the machine changes its states
** based on its current state and the character it encounters. if it is not in the correct
** state when reaching the end of the input string (OUTSIDE), the machine returns -1 to
** indicate an error ("open quotes").
*/

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
		return (-2);
	}
	return (0);
}

static int check_outside(e_state *state, bool *pipe_flag, char input)
{
	if (input == '|')
	{
		if (*pipe_flag == true)
			return (-3);
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

static int	scan_input(char *input)
{
	e_state	state;
	bool	pipe_flag;
	
	state = OUTSIDE;
	pipe_flag = true;
	while (*input)
	{
		if (state == OUTSIDE)
		{
			if (check_outside(&state, &pipe_flag, *input) < 0)
				return (-3);
		}
		else if (state == INSIDE_SINGLES && *input == '\'')
			state = OUTSIDE;
		else if (state == INSIDE_DOUBLES && *input == '\"')
			state = OUTSIDE;
		input++;
	}
	if (pipe_flag == true)
		return (-3);
	if (state != OUTSIDE)
		return (-4);
	return (0);
}

int	prelim_syn_check(char *input)
{
	int	res;

	if (check_if_empty(input) < 0)
		return (-1);
	if (check_if_only_whitespace(input) < 0)
		return (-2);
	res = scan_input(input);
	if (res == -3)
	{
		write(1, "syntax error: misplaced '|'\n", 28);
		return (-3);
	}
	if (res == -4)
	{
		write(1, "syntax error: open quotes\n", 26);
		return (-4);
	}
	return (0);
}