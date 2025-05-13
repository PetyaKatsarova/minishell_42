/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   termios.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/13 16:30:02 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/13 16:30:04 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

void	termios_sigquit_off(void)
{
	struct termios	termios_struct;

	write(1, "turned SIGQUIT off\n", 19);
	if (tcgetattr(0, &termios_struct) != 0)
	{
		perror("tcgetattr");
		exit (EXIT_FAILURE);
	}
	termios_struct.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(0, 0, &termios_struct) != 0)
	{
		perror("tcsetattr");
		exit (EXIT_FAILURE);
	}
}

void	termios_sigquit_on(void)
{
	struct termios	termios_struct;

	if (tcgetattr(0, &termios_struct) != 0)
	{
		perror("tcgetattr");
		exit (EXIT_FAILURE);
	}
	termios_struct.c_cc[VQUIT] = '\x1C';
	if (tcsetattr(0, 0, &termios_struct) != 0)
	{
		perror("tcsetattr");
		exit (EXIT_FAILURE);
	}
}
