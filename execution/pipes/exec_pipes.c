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
// NB !! on every pipe call handle_commands



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
