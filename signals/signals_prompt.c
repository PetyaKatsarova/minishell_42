/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   signals_prompt.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/13 16:29:48 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/13 16:29:49 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"
#include "../includes/minishell.h"

static void	sigint_prompt(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	setup_sigint_prompt(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_prompt;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGINT");
		return (-1);
	}
	return (0);
}

int	setup_sigquit_prompt(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGINT");
		return (-1);
	}
	return (0);
}
