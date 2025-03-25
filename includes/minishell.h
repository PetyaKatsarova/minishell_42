/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:28:45 by pekatsar          #+#    #+#             */
/*   Updated: 2025/03/25 16:50:37 by petya            ###   ########.fr       */
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
    int exported; // 1 = exported (visible to env/execve), 0 = local only
} t_env;

// execution/built_ins/*
int	    get_pwd();
int     do_cd(char **argv, t_env *env);
int     do_echo(char **args);
void    get_env(t_env   *env);

// execution/utils.c
void    free_arr(char **arr);
void    free_t_env(t_env *env_struct);

// execution/init.c
t_env   *init_env(char **env);
void    set_env_value(t_env *env, const char *key, const char *val);
char    *get_env_value(t_env *env, const char *key);
t_env   *copy_env(char **env);

#endif

