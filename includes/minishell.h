/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/15 16:58:08 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/15 16:58:11 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>
# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdint.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "parsing.h"
# include "signals.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef enum e_exit_status
{
	EXIT_INVALID_BUILTIN_ARGS = 2,
	EXIT_CMD_NOT_EXECUTABLE = 126,
	EXIT_CMD_NOT_FOUND = 127,
	EXIT_INVALID_EXIT_ARG = 128,
	EXIT_SIGNAL_BASE = 128
}	t_exit_status;

typedef struct s_env
{
	char	*key;
	char	*value;
	int		exported;
}	t_env;

typedef struct s_data
{
	int			i;
	int			pipe_count;
	int			**pipes;
	pid_t		*pids;
	t_node		*cmd;
	t_env_list	*env;
	t_tree		*tree;
}	t_data;

typedef struct s_env_list
{
	t_env	*vars;
	size_t	size;
	size_t	capacity;
	int		last_exit_status;
}	t_env_list;

typedef enum e_alloc_type
{
	ALLOC_MALLOC,
	ALLOC_STRDUP,
	ALLOC_STRJOIN,
	ALLOC_SUBSTR
}	t_alloc_type;

/* execution/built_ins */
int			get_pwd(char **argv);
int			do_cd(char **argv, t_env_list *env);
int			do_echo(char **args);
int			get_env(char **argv, t_env_list *env_struct);
int			do_export(char **args, t_env_list *env_struct);
int			do_exit(t_env_list *env_struct, t_tree *tree, t_node *cmd_node);
int			do_unset(char **args, t_env_list *env_struct);

/* export_utils + utils2 */
int			err_malloc(t_env_list *cpy, char *msg);
t_env_list	*cpy_env_list(t_env_list *env_struct);
t_env_list	*sort_env(t_env_list *env_struct);
void		print_env_export(t_env_list *sorted_env_struct);
int			process_export_args(char **args, t_env_list *env, int *has_error);

/* freeing */
void		free_arr(char **arr);
void		free_t_env(t_env_list *env_struct);

/* init */
void		set_env_value(t_env_list *env, const char *key, const char *val);
char		*get_env_value(t_env_list *env, const char *key);
t_env_list	*copy_env(char **env);
char		**converted_env(t_env_list *env_struct);
int			env_len(char **env);

/* utils */
int			too_many_args(char **args);
int			print_builtin_error(const char *cmd, const char *arg,
				const char *msg);
void		*xalloc(t_alloc_type type, void *a, void *b, size_t size);
void		close_all_pipe_fds(void);
void		total_liberation(t_tree *tree, t_env_list *env_list_struct,
				t_data *data, int **pipes);
void		setup_data_one(t_data *data, int i, int **pipes, t_tree *tree);
void		setup_data_two(t_data *data, pid_t *pids,
				t_node *cmd, t_env_list *env);

/* handle_commands */
int			execute_builtin(t_node *cmd, t_tree *tree, t_env_list *env);
int			handle_single_command(t_env_list *env, t_tree *tree,
				t_node *cmd);
void		free_data(t_data *data);

/* executables */
int			exec_on_path(t_env_list *env, t_node *cmd, int is_pipe);
void		update_exit_status(t_env_list *env_list, int status);
char		*get_command_path(t_env_list *env, char *cmd_no_flag);
void		free_dbl_ptr(char **ptr);
void		free_args(char **argv, int count);
int			is_valid_read_or_exec_file(char *file, char mode);

/* exec_pipes and redirects */
int			exec_pipeline(t_env_list *env, t_tree *tree);
int			perror_and_return(const char *message);
int			apply_redirections(t_node *cmd, int i);
int			apply_heredoc(t_node *redir, int i);
void		handle_child(t_data *data, int i);
void		close_all_pipes(int **pipes, int count);
int			wait_all(pid_t *pids, int count);

#endif
