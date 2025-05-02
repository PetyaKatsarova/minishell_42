/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 11:44:08 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/02 11:53:40 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

static void	parse_key_value(char *arg, char **key, char **value)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	*key = ft_substr(arg, 0, i);
	if (arg[i] == '=')
		*value = ft_strdup(arg + i + 1);
	else
		*value = NULL;
}

static int	has_space_around_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (i > 0 && arg[i - 1] == ' ')
		return (1);
	if (arg[i] == '=' && arg[i + 1] == ' ')
		return (1);
	return (0);
}

static int	append_replace_envvar(char *argv, t_env_list *env_struct)
{
	char	*key;
	char	*value;

	if (has_space_around_equal(argv))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	parse_key_value(argv, &key, &value);
	if (!key || !is_valid_identifier(key))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(key);
		free(value);
		return (EXIT_FAILURE);
	}
	set_env_value(env_struct, key, value);
	free(key);
	free(value);
	return (EXIT_SUCCESS);
}

int	process_export_args(char **args, t_env_list *env, int *has_error)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (append_replace_envvar(args[i], env) == EXIT_FAILURE)
			*has_error = 1;
		i++;
	}
	return (0);
}
