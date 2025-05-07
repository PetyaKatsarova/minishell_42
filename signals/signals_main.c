
#include "../includes/signals.h"
#include "../includes/minishell.h"

volatile int	g_state = STATE_NORMAL;

static void	handle_signal(int signum, siginfo_t *info, void *context)
{	
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{

		if (g_state == STATE_NORMAL)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			//
		}
		g_state = STATE_NORMAL;
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Failed to set up SIGINT handler");
		exit (1);
	}
}