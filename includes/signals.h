/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   signals.h                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/13 16:32:56 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/13 16:32:57 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

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

extern volatile sig_atomic_t	g_signum;

int		setup_sigint_heredoc(void);
int		setup_sigint_prompt(void);
int		setup_sigint_prompt_eof(void);
int		setup_sigint_ignore(void);
int		setup_signals_default(void);
int		setup_sigquit_prompt(void);
void	termios_sigquit_off(void);
void	termios_sigquit_on(void);

#endif
