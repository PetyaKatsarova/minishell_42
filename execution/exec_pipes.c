#include "../includes/minishell.h"

/**
 * Closes both ends of pipe[] and frees pipes[i] and pipes
 */
static void close_all_pipes(int **pipes, int count)
{
    if (!pipes)
        return;
    for (int i = 0; i < count; i++) {
        if (pipes[i]) {
            close(pipes[i][0]);
            close(pipes[i][1]);
            free(pipes[i]);
        }
    }
    free(pipes);
}



static int wait_all(pid_t *pids, int count)
{
	int status = 0;
	for (int i = 0; i < count; i++)
		waitpid(pids[i], &status, 0);
	return WEXITSTATUS(status);
}

/**
 * Creates pipe() for child[i], redirects pipe[0] to stdin & closes, pipe[1] to write stdout, closes pipe[1], after that executes command(builtin || executable)
 * (aka: read from stdin, write to stdout and execute cmd which reads/writes to/in tty(stdin/stdiout))
 */
static void handle_child(int i, int pipe_count, int **pipes, pid_t *pids, t_node *cmd, t_env_list *env, t_tree *tree)
{
	if (!cmd)
		exit(127);
	if (i > 0 && pipes[i - 1])
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < pipe_count && pipes[i])
		dup2(pipes[i][1], STDOUT_FILENO);

	close_all_pipes(pipes, pipe_count);
	free(pids);

	if (apply_redirections(cmd) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);

	int status = execute_builtin(cmd, tree, env);
	if (status != EXIT_CMD_NOT_FOUND)
		exit(status);
	exec_on_path(env, cmd, 1);
	exit(EXIT_CMD_NOT_FOUND);
}

int exec_pipeline(t_env_list *env, t_tree *tree)
{
	int pipe_count = get_num_pipes(tree);
	int **pipes = malloc(sizeof(int *) * (pipe_count));
    for (int i = 0; i < pipe_count; i++)
    {
        pipes[i] = NULL;
    }
       
	pid_t *pids = malloc(sizeof(pid_t) * (pipe_count + 1));
	t_node *cmd = go_first_cmd(tree);
	int i = 0;

	if (!pipes || !pids)
		exit(EXIT_FAILURE);
	while (cmd)
	{
		if (i < pipe_count)
		{
			pipes[i] = malloc(sizeof(int) * 2);
			if (!pipes[i] || pipe(pipes[i]) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
			handle_child(i, pipe_count, pipes, pids, cmd, env, tree);
		if (i > 0 && pipes[i - 1])
		{
			close(pipes[i - 1][0]); // close both ends of prev pipe
			close(pipes[i - 1][1]);
		}
		cmd = go_next_cmd(cmd);
		i++;
	}

	int status = wait_all(pids, i);
	env->last_exit_status = status;
    close_all_pipes(pipes, pipe_count);
	free(pids);
	return status;
}


