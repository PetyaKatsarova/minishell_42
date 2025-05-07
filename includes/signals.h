
#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <sys/ioctl.h>

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

extern volatile int	g_state;

typedef enum	s_global_state
{
	STATE_NORMAL,
	STATE_HEREDOC
}	t_global_state;

void	setup_signals(void);

#endif