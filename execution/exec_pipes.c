#include "../includes/minishell.h"

static void close_all_pipes(int **pipes, int count)
{
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

static void handle_child(int i, int pipe_count, int **pipes, t_node *cmd,
	t_env_list *env, t_tree *tree)
{
	if (!cmd)
		exit(127);
	if (i > 0 && i - 1 < pipe_count && pipes[i - 1])
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i-1][0]);
	}
	if (i < pipe_count && pipes[i])
	{
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
	int status = execute_builtin(cmd, tree, env);
	if (status != -1)
		exit(status);
	exit(exec_on_path(env, cmd, 1));
}

int exec_pipeline(t_env_list *env, t_tree *tree)
{
	int pipe_count = get_num_pipes(tree);
	int **pipes = malloc(sizeof(int *) * pipe_count);
	pid_t *pids = malloc(sizeof(pid_t) * (pipe_count + 1));
	t_node *cmd = go_first_cmd(tree);
	int i = 0;

	if (!pipes || !pids)
		return (EXIT_FAILURE);

	while (cmd) {
		if (i < pipe_count) {
			pipes[i] = malloc(sizeof(int) * 2);
			if (!pipes[i] || pipe(pipes[i]) < 0) {
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pids[i] = fork();
		if (pids[i] == 0)
			handle_child(i, pipe_count, pipes, cmd, env, tree);
		if (pids[i] > 0) {
			if (i > 0 && pipes[i - 1])
				close(pipes[i - 1][0]);
			if (i < pipe_count && pipes[i])
				close(pipes[i][1]);
		}
		cmd = go_next_cmd(cmd);
		i++;
	}
	close_all_pipes(pipes, pipe_count);
	int result = wait_all(pids, i);
	free(pids);
	return result;
}
