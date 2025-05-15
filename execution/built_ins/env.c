/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 11:31:23 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/02 11:32:56 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	_=/usr/bin/env_lst
	The last command run was /usr/bin/env_lst, and _ was set to that.
*/

static void	write_key_vals(t_env_list *env_struct, int i)
{
	int	slen_val;
	int	slen_key;

	slen_val = ft_strlen(env_struct->vars[i].value);
	slen_key = ft_strlen(env_struct->vars[i].key);
	write(STDOUT_FILENO, env_struct->vars[i].key, slen_key);
	write(STDOUT_FILENO, "=", 1);
	write(STDOUT_FILENO, env_struct->vars[i].value, slen_val);
	write(STDOUT_FILENO, "\n", 1);
}

static void	write_stderr(const char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
}

int	get_env(char **argv, t_env_list *env_struct)
{
	size_t	i;

	(void)argv;
	i = 0;
	if (!env_struct || !env_struct->vars)
	{
		write_stderr("mshell: env: Environment not initialized\n");
		return (EXIT_FAILURE);
	}
	while (i < env_struct->size
		&& ft_strncmp(env_struct->vars[i].key, "PATH", 4))
		i++;
	if (argv[1])
		return (write_stderr("mshell: env: No such file or directory\n"), 127);
	i = 0;
	while (i < env_struct->size)
	{
		if (env_struct->vars[i].key && env_struct->vars[i].value
			&& env_struct->vars[i].exported)
			write_key_vals(env_struct, i);
		i++;
	}
	return (EXIT_SUCCESS);
}
