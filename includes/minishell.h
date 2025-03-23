/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:28:45 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/20 15:57:08 by pekatsar      ########   odam.nl         */
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

// execution/built_ins/*
int	get_pwd();
int	do_cd(char **argv, char **env);

#endif

