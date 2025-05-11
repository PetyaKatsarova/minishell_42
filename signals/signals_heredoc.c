#include "../includes/signals.h"
#include "../includes/minishell.h"

static void	sigint_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}

int	setup_sigint_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	//sigaddset(&sa.sa_mask, SIGQUIT);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGINT");
		return(-1);
	}
	// if (sigaction(SIGQUIT, &sa, NULL) == -1)
	// {
	// 	perror("sigaction for SIGQUIT");
	// 	return (-1);
	// }
	return (0);
}
