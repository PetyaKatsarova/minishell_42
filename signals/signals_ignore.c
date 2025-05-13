/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   signals_ignore.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/13 16:29:22 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/13 16:29:23 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"
#include "../includes/minishell.h"

int	setup_sigint_ignore(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGINT");
		return (-1);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGQUIT");
		return (-1);
	}
	return (0);
}
