/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/17 11:55:42 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/18 15:11:04 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define CWD_MAX 1024

/*
cd
Use the command cd to move the working directory and check if you are in the right directory with /bin/ls: !!NB!! /bin/ls is the actual binary of the ls command — the one that lists files.
Repeat multiple times with working and not working cd
Also, try '.' and '..' as arguments.
pwd
Use the command pwd.
Repeat multiple times in different directories.
Relative Path
Execute commands but this time use a relative path.
Repeat multiple times in different directories with a complex relative path (lots of ..).
Environment path
Execute commands but this time without any path (ls, wc, awk and so forth).
Unset the $PATH and ensure commands are not working anymore.
Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in
order from left to right.
bash: cd: HOME not set

1. cd ✓
2. cd ~ ✓
3 !! todo: cd bla: 4 bytes leaked in 1 allocation
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

