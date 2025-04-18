/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   exec_pipes.c									   :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/04/02 17:10:40 by pekatsar	  #+#	#+#				 */
/*   Updated: 2025/04/02 17:10:45 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
for each cmd i:
	if (i < N - 1)
		pipe(pipefd[i]);

	fork();
	if (child)
	{
		if (i > 0)
			dup2(pipefd[i-1][0], STDIN_FILENO); // read from prev
		if (i < N - 1)
			dup2(pipefd[i][1], STDOUT_FILENO); // write to next
		close all pipes
		execve(cmd[i][0], cmd[i], envp);
	}

*/

/**
 * Executes a pipeline of commands, where each command is a **args[i]
 * args = {
	{"ls", "-l", NULL},
	{"grep", ".c", NULL},
	{"wc", "-l", NULL},
	NULL
};
 */

static void	setup_child_pipes(int i, int num_cmds, int prev_fd, int pipefd[2])
{
	if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (i < num_cmds - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	if (i < num_cmds - 1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

static void	parent_pipe_control(int i, int num_cmds, int pipefd[2], int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i < num_cmds - 1)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

static void	execute_single_child(char **cmd, t_env_list *env)
{
	if (is_builtin(cmd[0]))
		run_builtin(cmd, env, 1);
	else
		exec_command(env, cmd); // todo: add in execcommand if child param
	exit(EXIT_SUCCESS);
}

void	execute_pipes(char ***args, t_env_list *env_lst)
{
	int		i = 0;
	int		num_cmds = 0;
	int		pipefd[2];
	int		prev_fd = -1;
	int		status = 0;
	pid_t	pid, last_pid;

	while (args[num_cmds])
		num_cmds++;
	while (i < num_cmds)
	{
		if (i < num_cmds - 1 && pipe(pipefd) == -1)
			return (perror("pipe failed"));
		pid = fork();
		if (pid == -1)
			return (perror("fork failed"));
		if (pid == 0)
		{
			setup_child_pipes(i, num_cmds, prev_fd, pipefd);
			execute_single_child(args[i], env_lst);
		}
		last_pid = pid;
		parent_pipe_control(i, num_cmds, pipefd, &prev_fd);
		i++;
	}
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		env_lst->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		env_lst->last_exit_status = 128 + WTERMSIG(status);
}

/**
 * THEORY:
 * pipe(pipefd): creates a new pipe (read/write ends)

fork():

In the child:

dup2(prev_fd, STDIN_FILENO) → get input from previous pipe (if any)

dup2(pipefd[1], STDOUT_FILENO) → send output to next pipe

Run command via execve (or run_builtin)

In the parent:

Closes used pipe ends

Waits for child

prev_fd = pipefd[0] → stores current read-end for next child

Output of cmd[i] goes to STDOUT_FILENO, which is redirected via pipefd[1]

Input of cmd[i+1] comes from STDIN_FILENO, which is set to prev_fd = pipefd[0]

Parent never touches the data — pipes connect child ↔ child

ln -s /tmp mylink
cd mylink
pwd        # Should reflect correctly
Command				Explanation
ln -s /tmp/ mylink	Creates a symbolic link (a shortcut) called mylink that points to /tmp.
cd mylink			You cd into the mylink, which is a symlink → so you’re actually now in /tmp.
pwd					Shows your current directory → prints /tmp, not ./mylink.
ls					Lists the contents of /tmp directory. All the systemd-private-* are temporary files created by the system.

what is symlink: Like a shortcut in Windows/macOS.

Doesn’t copy the folder, just points to it.

If you rm mylink, it deletes the link, not /tmp.
 */
