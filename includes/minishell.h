/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   minishell.h										:+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/04/10 13:44:06 by pekatsar	  #+#	#+#				 */
/*   Updated: 2025/04/10 13:44:09 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>  // for stats func and MACROS: S_ISLNK(m) S_ISDIR(m) S_ISREG(m)
# include "../libs/libft/libft.h"
//# include <readline/readline.h>
//# include <readline/history.h>
# include <stdlib.h> // exit
# include <unistd.h> // fork, execve, access, read, write, close, dup2, pipe
# include <limits.h> // is it allowed? <limits.h> defines system limits like max values for integers, file paths, and system resources. for PATH_MAX: NOT IN ALL OS
# include <stdio.h> // perror
# include <string.h> //?? what for
# include <errno.h> // is it allowed?
# include <stdint.h> // for uint8_t
# include <sys/wait.h> /// waitpid, WIFEXITED, WEXITSTATUS
#include <fcntl.h>     // for open(), O_RDONLY, O_WRONLY, etc.
//# include <stdbool.h>
# include "parsing.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/*
The t_shell_exit_status enum is a type definition, and its purpose is to provide a named type for the exit status values. However, when using the enum values (EXIT_SUCCESS, EXIT_CMD_NOT_FOUND), you don't need to explicitly reference the type name (t_shell_exit_status) because the enum values are globally accessible constants.
*/
typedef enum e_exit_status
{
    // EXIT_SUCC = 0, use EXIT_SUCCESS from stdlib.h
    // EXIT_GEN_ERR = 1, use EXIT_FAILURE from stdlib.h
    EXIT_INVALID_BUILTIN_ARGS = 2,
    EXIT_CMD_NOT_EXECUTABLE = 126,
    EXIT_CMD_NOT_FOUND = 127,
    EXIT_INVALID_EXIT_ARG = 128,
    EXIT_SIGNAL_BASE = 128, // kill -9 => 137 = 128+9
	EXIT_NO_EXECUTABLE = -1
}   t_exit_status;

typedef struct s_env {
	char	*key;
	char	*value;
	int	 	exported; // by default set to 1 = exported (visible to env/execve), 0 = local only
} t_env;
	
/*
size: how many environment variables are currently stored
capacity: how many variables can fit before realloc is needed
*/
typedef struct s_env_list {
	t_env   *vars;
	size_t  size;
	size_t  capacity;
	int	 last_exit_status; //Every time a command runs → set shell->last_status = exit_code
	int  is_child; // 1 if child process, 0 if parent, default is 0
} t_env_list;

// execution/built_ins/*
int			get_pwd();
int		 	do_cd(char **argv, t_env_list *env);
int		 	do_echo(char **args);
int		 	get_env(t_env_list   *env_struct);
int		 	do_export(char  **input_args, t_env_list *env_struct);
int		 	do_exit(t_env_list *env_struct, t_tree *tree, t_node *cmd_node);
int		 	do_unset(char **input_args, t_env_list *env_struct);

// execution/export_utils.c
int			err_malloc(t_env_list *cpy, char *msg);
t_env_list  *cpy_env_list(t_env_list *env_struct);
t_env_list  *sort_env(t_env_list *env_struct);
void		print_env_export(t_env_list *sorted_env_struct);

// execution/freeing.c
void		free_arr(char **arr);
void		free_t_env(t_env_list *env_struct);

// execution/init.c
void		set_env_value(t_env_list *env_list, const char *key, const char *val);
char		*get_env_value(t_env_list *env_list, const char *key);
t_env_list  *copy_env(char **env);
char 		**converted_env(t_env_list *env_struct);

// execution/utils.c
int			too_many_args(char	**input_args);
int			print_builtin_error(const char *cmd, const char *arg, const char *msg);

// execution/handle_commands.c
//int 		handle_command(t_env_list *env, t_tree *tree, t_node *curr_cmd);
int 		execute_builtin(t_node *cmd_node, t_tree *tree, t_env_list *env_struct);

// execution/executables/*
int			exec_on_path(t_env_list *env_list, t_node	*curr_cmd, int is_pipe);
char		*get_command_path(t_env_list *env, char *cmd_no_flag);
void		free_dbl_ptr(char **ptr);
void		free_args(char **argv, int count);
int			is_valid_read_or_exec_file(char *file_name, char mode);

// execution/exec_pipes.c
int         exec_pipeline(t_env_list *env, t_tree *tree);

#endif
