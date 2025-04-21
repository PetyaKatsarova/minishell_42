// src/exec/exec_pipes.c

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

static void handle_child(int i, int n, int **pipes, t_node *cmd,
	t_env_list *env, t_tree *tree)
{
	if (!cmd) {
		exit(127);
	}
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < n - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	//for (int j = 0; j < n - 1; j++) {
	//	if (pipes[j]) {
	//		close(pipes[j][0]);
	//		close(pipes[j][1]);
	//	}
	//}
	int status = execute_builtin(cmd, tree, env);
	if (status != -1)
		exit(status);
	exit(exec_on_path(env, cmd, 1));
}

int exec_pipeline(t_env_list *env, t_tree *tree)
{
	int n = get_num_pipes(tree) + 1;
	int **pipes = malloc(sizeof(int *) * (n - 1));
	pid_t *pids = malloc(sizeof(pid_t) * n);
	t_node *cmd = go_first_cmd(tree);
	for (int i = 0; i < n && cmd; i++) {
		if (i < n - 1) {
			pipes[i] = malloc(sizeof(int) * 2);
			pipe(pipes[i]);
		}
		pids[i] = fork();
		if (pids[i] == 0)
			handle_child(i, n, pipes, cmd, env, tree);
		cmd = go_next_cmd(cmd);
	}
	close_all_pipes(pipes, n - 1);
	int result = wait_all(pids, n);
	free(pids);
	return result;
}
