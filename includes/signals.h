
#ifndef SIGNALS_H
# define SIGNALS_H

# define _DEFAULT_SOURCE 1

# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

extern volatile int	g_signum;

int		setup_sigint_heredoc(void);
int		setup_sigint_prompt(void);
int		setup_sigint_prompt_eof(void);
void	termios_sigquit_off(void);
void	termios_sigquit_on(void);

#endif