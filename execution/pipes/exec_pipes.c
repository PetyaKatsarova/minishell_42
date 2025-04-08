/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipes.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/02 17:10:40 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/02 17:10:45 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void execute_pipes(char ***commands, t_env_list *env_lst)
{
    int i = 0, num_pipes = 0;
    int pipefd[2], prev_fd = 0; // prev_fd stores the read end of the previous pipe
    pid_t pid;

    // Count the number of commands (and thus the number of pipes)
    while (commands[num_pipes])
        num_pipes++;

    while (commands[i])
    {
        // Create a pipe for all but the last command
        if (i < num_pipes - 1)
            pipe(pipefd);

        pid = fork();
        if (pid == 0) // Child process
        {
            // Redirect input from the previous pipe (if not the first command)
            if (prev_fd != 0)
                dup2(prev_fd, STDIN_FILENO);

            // Redirect output to the current pipe (if not the last command)
            if (i < num_pipes - 1)
                dup2(pipefd[1], STDOUT_FILENO);

            // Close unused pipe ends
            if (i < num_pipes - 1)
            {
                close(pipefd[0]);
                close(pipefd[1]);
            }

            // Execute the built-in command
            if (strcmp(commands[i][0], "env") == 0)
                get_env_lst(env_lst);
            else
                fprintf(stderr, "Unknown command: %s\n", commands[i][0]);

            exit(0); // Exit the child process
        }
        else // Parent process
        {
            // Close the write end of the current pipe
            if (i < num_pipes - 1)
                close(pipefd[1]);

            // Update prev_fd to the read end of the current pipe
            prev_fd = pipefd[0];

            // Wait for the child process to finish
            waitpid(pid, NULL, 0);
        }

        i++;
    }
}
