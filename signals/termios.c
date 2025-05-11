
#include "../includes/signals.h"

void	set_terminal(void)
{
	static struct termios	termios_old;
	struct termios			termios_new;

	if (tcgetattr(0, &termios_old) != 0)
	{
		perror("tcgetattr");
		exit (EXIT_FAILURE);
	}
	termios_new = termios_old;
	termios_new.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(0, 0, &termios_new) != 0)
	{
		perror("tcsetattr");
		exit (EXIT_FAILURE);
	}
}

void	reset_terminal(void)
{
	static struct termios	termios_old;
	struct termios			termios_new;

	if (tcgetattr(0, &termios_old) != 0)
	{
		perror("tcgetattr");
		exit (EXIT_FAILURE);
	}
	termios_new = termios_old;
	termios_new.c_cc[VQUIT] = '\x1C';
	if (tcsetattr(0, 0, &termios_new) != 0)
	{
		perror("tcsetattr");
		exit (EXIT_FAILURE);
	}
}
