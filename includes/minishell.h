/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:28:45 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/26 17:41:04 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h> // is it allowed? <limits.h> defines system limits like max values for integers, file paths, and system resources.
#include <stdio.h>
#include <string.h>
#include <errno.h> // is it allowed?

typedef struct s_env {
    char *key;
    char *value;
    int exported; // by default set to 1 = exported (visible to env/execve), 0 = local only
} t_env;

// execution/built_ins/*
int	    get_pwd();
int     do_cd(char **argv, t_env *env);
int     do_echo(char **args);
void    get_env(t_env   *env); // maybe do it int?
int     do_export(char  **input_args, t_env *env_struct);
int     do_exit(char **input_args, char *input);

// execution/freeing.c
void    free_arr(char **arr);
void    free_t_env(t_env *env_struct);

// execution/init.c
//t_env   *init_env(char **env);
void    set_env_value(t_env *env, const char *key, const char *val);
char    *get_env_value(t_env *env, const char *key);
t_env   *copy_env(char **env);
void    set_export_flag(t_env *env_struct, const char *key); // do i need it?

#endif

