#include "../includes/signals.h"
#include "../includes/minishell.h"

static void	sigint_prompt_eof(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = SIGINT;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	setup_sigint_prompt_eof(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_prompt_eof;
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
