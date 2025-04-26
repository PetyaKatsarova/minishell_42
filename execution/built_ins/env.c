/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/17 11:56:26 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/26 08:45:17 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
_=/usr/bin/env_lst
the last command run was /usr/bin/env_lst, and _ was set to that.
*/

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
			printf("%s=%s\n", env_struct->vars[i].key, env_struct->vars[i].value);
		i++;
	}
	return (EXIT_SUCCESS);
}
