/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipes.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/21 13:59:06 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/21 14:29:37 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

//static void setup_redirects(t_node *cmd)
//{
//	if (!cmd || !cmd->redirects)
//		return;

//	t_node *redir = cmd->redirects;
//	int fd;

//	while (redir) {
//		if (!redir->redir_path) {
//			redir = redir->redirects;
//			continue;
//		}
//		if (redir->token_type == TOKEN_INPUT_REDIRECT)
//			fd = open(redir->redir_path, O_RDONLY);
//		else if (redir->token_type == TOKEN_OUTPUT_REDIRECT)
//			fd = open(redir->redir_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
//		else if (redir->token_type == TOKEN_APPEND_OUTPUT_REDIRECT)
//			fd = open(redir->redir_path, O_CREAT | O_WRONLY | O_APPEND, 0644);
//		else if (redir->token_type == TOKEN_HEREDOC)
//			fd = open(redir->redir_path, O_RDONLY);
//		else {
//			redir = redir->redirects;
//			continue;
//		}
//		if (fd < 0) {
//			perror("open failed in redirection");
//			exit(1);
//		}
//		if (redir->token_type == TOKEN_INPUT_REDIRECT || redir->token_type == TOKEN_HEREDOC)
//			dup2(fd, STDIN_FILENO);
//		else
//			dup2(fd, STDOUT_FILENO);
//		close(fd);
//		redir = redir->redirects;
//	}
//}

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
/**
 * 
 */
static int wait_all(pid_t *pids, int count)
{
	int status = 0;
	int i = 0;

	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	return WEXITSTATUS(status);
}
/**
 * Builtins like cd, exit must run in parent only if no pipe. Others (e.g. echo, pwd, env) can run in child
 */
int exec_pipeline(t_env_list *env, t_tree *tree)
{
	int n = get_num_pipes(tree) + 1;
	int **pipes = malloc(sizeof(int *) * (n - 1));
	if (!pipes) return 1;
	pid_t *pids = malloc(sizeof(pid_t) * n);
	if (!pids) return 1;
	t_node *cmd = go_first_cmd(tree);

	for (int i = 0; i < n; i++) {
		if (!cmd) {
			fprintf(stderr, "Error: cmd NULL at step %d\n", i);
			break;
		}

		if (i < n - 1) {
			pipes[i] = malloc(sizeof(int) * 2);
			if (!pipes[i] || pipe(pipes[i]) < 0) {
				perror("pipe");
				exit(1);
			}
		}
		pids[i] = fork();
		if (pids[i] == 0) {
			if (!cmd || !cmd->argv || !cmd->argv[0]) exit(127);
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < n - 1)
				dup2(pipes[i][1], STDOUT_FILENO);

			for (int j = 0; j < n - 1; j++) {
				if (pipes[j]) {
					close(pipes[j][0]);
					close(pipes[j][1]);
				}
			}

			//setup_redirects(cmd);
			exec_on_path(env, cmd, 1);
			exit(127);
		}
		cmd = go_next_cmd(cmd);
	}
	close_all_pipes(pipes, n - 1);
	int result = wait_all(pids, n);
	free(pids);
	return result;
}

