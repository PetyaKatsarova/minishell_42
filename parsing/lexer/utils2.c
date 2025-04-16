#include "../minishell.h"

int	set_state(e_state state, char c)
{
	if (state == OUTSIDE)
	{
		if (c == '\'')
		{
			state = INSIDE_SINGLES;
		}
		else if (c == '\"')
		{
			state = INSIDE_DOUBLES;
		}
	}
	else if (c == '\'' || c == '\"')
	{
		state = OUTSIDE;
	}
	//printf("set_state: state: %d\n", state);
	return (state);
}