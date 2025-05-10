
#include "../includes/signals.h"
#include "../includes/minishell.h"

volatile int	g_signum = 0;

static void	sigquit(int signum)
{

}

int	setup_sigquit(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = sigquit;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGQUIT");
		return (-1);
	}	
}

static void	sigint_prompt(int signum)
{
	g_signum = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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

static void	sigint_prompt_eof(int signum)
{
	g_signum = SIGINT;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	setup_sigint_prompt_eof(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_prompt_eof;
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

static void	sigint_heredoc(int signum)
{
	g_signum = SIGINT;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

int	setup_sigint_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGINT");
		return(-1);
	}
	return (0);
}

static void	sigint_parsing(int signum)
{
	g_signum = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	setup_sigint_parsing(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_parsing;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGINT");
		return(-1);
	}
	return (0);
}