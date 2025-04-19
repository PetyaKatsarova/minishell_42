
#include "../../includes/parsing.h"

// static int	check_pipes(char **input)
// {
// 	bool	pipe_flag;

// 	pipe_flag = true;
// 	while (**input && **input != '\'' && **input != '\"')
// 	{
// 		if (**input == '|')
// 		{
// 			if (pipe_flag == true)
// 			{
// 				return (-2);
// 			}
// 			else
// 			{
// 				pipe_flag = true;
// 			}
// 		}
// 		else if (is_whitespace(**input) == false)
// 		{
// 			pipe_flag = false;
// 		}
// 		(*input)++;
// 	}
// 	if (pipe_flag == true)
// 	{
// 		return (-2);
// 	}
// 	return (0);
// }

/*
** this function uses the logic of a state machine. the machine changes its states
** based on its current state and the character it encounters. if it is not in the correct
** state when reaching the end of the input string (OUTSIDE), the machine returns -1 to
** indicate an error ("open quotes").
*/

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
			if (*input == '|')
			{
				if (pipe_flag == true)
					return (-2);
				else
					pipe_flag = true;
			}
			else if (is_whitespace(*input) == false)
				pipe_flag = false;
			if (*input == '\'')
				state = INSIDE_SINGLES;
			else if (*input == '\"')
				state = INSIDE_DOUBLES;
		}
		else if (state == INSIDE_SINGLES && *input == '\'')
			state = OUTSIDE;
		else if (state == INSIDE_DOUBLES && *input == '\"')
			state = OUTSIDE;
		input++;
	}
	if (pipe_flag == true)
		return (-2);
	if (state != OUTSIDE)
		return (-1);
	return (0);
}

int	prelim_syn_check(char *input)
{
	int	res;

	res = scan_input(input);
	if (res == -1)
	{
		write(1, "syntax error: open quotes\n", 26);
		return (-1);
	}
	if (res == -2)
	{
		write(1, "syntax error: misplaced '|'\n", 28);
		return (-2);
	}
	return (0);
}