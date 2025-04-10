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

#include <sys/stat.h>  // for stats func and MACROS: S_ISLNK(m) S_ISDIR(m) S_ISREG(m)
# include "../libs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h> // is it allowed? <limits.h> defines system limits like max values for integers, file paths, and system resources. for PATH_MAX: NOT IN ALL OS
#include <stdio.h>
#include <string.h>
#include <errno.h> // is it allowed?
#include <stdint.h> // for uint8_t

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/*
The t_shell_exit_status enum is a type definition, and its purpose is to provide a named type for the exit status values. However, when using the enum values (EXIT_SUCCESS, EXIT_CMD_NOT_FOUND), you don't need to explicitly reference the type name (t_shell_exit_status) because the enum values are globally accessible constants.
*/
typedef enum e_exit_status
{
    EXIT_SUCC = 0,
    EXIT_GEN_ERR = 1,
    EXIT_INVALID_BUILTIN_ARGS = 2,
    EXIT_CMD_NOT_EXECUTABLE = 126,
    EXIT_CMD_NOT_FOUND = 127,
    EXIT_INVALID_EXIT_ARG = 128,
    EXIT_SIGNAL_BASE = 128 // kill -9 => 137 = 128+9
}   t_exit_status;

typedef struct s_env {
	char	*key;
	char	*value;
	int	 exported; // by default set to 1 = exported (visible to env/execve), 0 = local only
} t_env;
	
/*
size: how many environment variables are currently stored
capacity: how many variables can fit before realloc is needed
*/
typedef struct s_env_list {
	t_env   *vars;
	size_t  size;
	size_t  capacity;
	int	 shlvl; // shell level
	int	 last_exit_status; //Every time a command runs → set shell->last_status = exit_code
} t_env_list;

// execution/built_ins/*
int			get_pwd();
int		 do_cd(char **argv, t_env_list *env);
int		 do_echo(char **args);
int		 get_env(t_env_list   *env);
int			get_env_struct_len(t_env_list *env_struct);
int		 do_export(char  **input_args, t_env_list *env_struct);
int		 do_exit(char **input_args, char *input, t_env_list *env_struct);
int		 do_unset(char **input_args, t_env_list *env_struct);
int			handle_builtins(char **input_args, t_env_list *env_struct, char *input);

// execution/export_utils.c
int		err_malloc(t_env_list *cpy, char *msg);
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
void		unset_export_flag(t_env_list *env_list, const char *key);

// execution/utils.c
int			too_many_args(char	**input_args);
int			print_builtin_error(const char *cmd, const char *arg, const char *msg);
long		ft_atol(const char *str);
// char *expand_dollar_vars(const char *input, t_env_list env_lst); TODO

// execution/expand_dollar.c
char		**expand_input_args(char **input_args);
//void	set_export_flag(t_env *env_struct, const char *key); // do i need it?

#endif
