/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/18 15:12:55 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/25 10:39:48 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define CWD_MAX 1024

/**
 * Parses full command path in the **result, returns exit_success(0) or failure(1)
 */
static int	cd_to_home_or_join(char *rest, char *home, char **result)
{
	if (rest[0] == '\0')
		*result = ft_strdup(home);
	else if (rest[0] == '/')
		*result = ft_strjoin(home, rest);
	else
		*result = ft_strdup(rest);
	if (!*result)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	update_pwd(t_env_list *env)
{
	char	cwd[CWD_MAX];

	if (getcwd(cwd, CWD_MAX))
		set_env_value(env, "PWD", cwd);
}

static int	handle_cd_home(char **input_args, t_env_list *env)
{
	char	*home;
	char	*rest;
	char	*result;

	home = get_env_value(env, "HOME");
	if (!home)
		return (print_builtin_error("cd", NULL, " HOME not set"));
	if (!input_args[1])
	{
		if (chdir(home) != 0)
			return (print_builtin_error("cd", NULL, " Failed to change directory"));
		update_pwd(env);
		return (EXIT_SUCCESS);
	}
	if (input_args[1][0] != '~')
		return (EXIT_SUCCESS);
	rest = input_args[1] + 1;
	if (cd_to_home_or_join(rest, home, &result) != 0)
		return (EXIT_FAILURE);
	if (chdir(result) != 0)
		return (free(result), print_builtin_error("cd", result, " Failed to change directory"));
	update_pwd(env);
	free(result);
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles cd, cd ~, cd ~/path, cd -, cd .., cd ./path
 */
int do_cd(char **input_args, t_env_list *env)
{
	char cwd[CWD_MAX];
	char *result;

	if (too_many_args(input_args))
		return (print_builtin_error("cd", NULL, " too many arguments"));
	char *oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (print_builtin_error("cd", NULL, " Failed to get current directory"));
	set_env_value(env, "OLDPWD", oldpwd);
	free(oldpwd);
	if (!input_args[1] || (input_args[1] && input_args[1][0] == '~'))
		return (handle_cd_home(input_args, env));
	else
		result = ft_strdup(input_args[1]);
	if (!result)
		return (print_builtin_error("strdup", NULL, " malloc failed"));
	if  (chdir(result) != 0)
	{
		int err = print_builtin_error("cd", result, " Failed to change directory");
        return (free(result), err);
    }
	if (getcwd(cwd, CWD_MAX))
		set_env_value(env, "PWD", cwd);
	free(result);
	return (EXIT_SUCCESS);
}

