/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/17 11:56:26 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/30 16:03:22 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
_=/usr/bin/env_lst
the last command run was /usr/bin/env_lst, and _ was set to that.
*/

static void write_key_vals(t_env_list *env_struct, int i)
{
	int slen_val;
	int slen_key;

	slen_val = ft_strlen(env_struct->vars[i].value);
	slen_key = ft_strlen(env_struct->vars[i].key);
	write(STDOUT_FILENO, env_struct->vars[i].key, slen_key);
	write(STDOUT_FILENO, "=", 1);
	write(STDOUT_FILENO, env_struct->vars[i].value, slen_val);
	write(STDOUT_FILENO, "\n", 1);
}

int	get_env(char **argv, t_env_list *env_struct)
{
	size_t	i;

	i = 0;
	if (!env_struct || !env_struct->vars)
	{
		write(STDERR_FILENO, "minihell: env: Environment not initialized\n", 44);
		return (EXIT_FAILURE);
	}
	while (i < env_struct->size && ft_strncmp(env_struct->vars[i].key, "PATH", 4))
		i++;
	if (i == env_struct->size || !env_struct->vars[i].value ||argv[1])
	{
		write(STDERR_FILENO, "minihell: env: No such file or directory\n", 41);
		return (127);
	}

	i = 0;
	while (i < env_struct->size)
	{
		if (env_struct->vars[i].key && env_struct->vars[i].value
			&& env_struct->vars[i].exported)
			// printf("%s=%s\n", env_struct->vars[i].key, env_struct->vars[i].value);
			write_key_vals(env_struct, i);
		i++;
	}
	return (EXIT_SUCCESS);
}
