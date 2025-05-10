
#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <sys/ioctl.h>

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

extern volatile int	g_signum;

int	setup_sigint_heredoc(void);
int	setup_sigint_interactive(void);
int	setup_sigint_interactive_eof(void);
int	setup_sigquit(void);

#endif