
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
