/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/02 13:34:25 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/02 16:26:29 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **expand_input_args(char **input_args)
{
	//char **updated_input_args;

	// iter all args: 
	// if $? or $valid_env_var substitute str with value, treat invalid $invalid_env_var as normal str, if nth replaced: return original inputargs, otherwise, return the new mallocd **str
	return (input_args);
}