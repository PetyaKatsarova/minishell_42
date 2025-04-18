
#include "../../includes/parsing.h"

/*
** this function uses the logic of a state machine. this machine changes its states
** based on its current state and the character it encounters. if it is not in the correct
** state when reaching the end of the input string (OUTSIDE), the machine returns -1 to
** indicate an error.
*/

int	check_quotes(char *input)
{
	e_state	state;
	
	state = OUTSIDE;
	while (*input)
	{
		if (state == OUTSIDE)
		{
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
	if (state != OUTSIDE)
		return (-1);
	return (0);
}
