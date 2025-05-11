
#include "../includes/signals.h"

void	set_terminal(void)
{
	struct termios	termios;

	if (tcgetattr(0, &termios) != 0)
	{
		perror("tcgetattr");
		exit (EXIT_FAILURE);
	}
	termios.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(0, 0, &termios) != 0)
	{
		perror("tcsetattr");
		exit (EXIT_FAILURE);
	}
}

void	reset_terminal(void)
{
	struct termios	termios;

	if (tcgetattr(0, &termios) != 0)
	{
		perror("tcgetattr");
		exit (EXIT_FAILURE);
	}
	termios.c_cc[VQUIT] = '\x1C';
	if (tcsetattr(0, 0, &termios) != 0)
	{
		perror("tcsetattr");
		exit (EXIT_FAILURE);
	}
}
