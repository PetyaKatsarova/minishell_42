/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:14:07 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/13 15:40:20 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Splits the PATH environment variable into an array of paths.
 */
static char	**split_path(t_env_list *env_list)
{
	int		i;
	char	**env;
	char	**arr;

	env = converted_env(env_list);
	if (!env)
		return (write(2, "Error in converting env\n", 24), NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			arr = ft_split(env[i] + 5, ':');
			free_arr(env);
			if (!arr)
			return (write(2, "Error in splitting PATH.\n", 26),
					free_arr(env), NULL);
			return (arr);
		}
		i++;
	}
	return (write(2, "PATH not found in env.\n", 24), free_arr(env), NULL);
}

/**
 * Joins and returns path with cmd name like: /bin + ls = /bin/ls
 */
static char	*build_full_command_path(char *path, char *command_no_flag)
{
	char	*with_line;
	char	*full_path;

	with_line = ft_strjoin(path, "/");
	if (!with_line)
		return (write(2, "ft_strjoin with_line failed\n", 29), NULL);
	full_path = ft_strjoin(with_line, command_no_flag);
	free(with_line);
	if (!full_path)
		write(2, "ft_strjoin full_path failed\n", 29);
	return (full_path);
}

static char	*get_full_path(char **paths, char *command_no_flag, int *found)
{
	char	*full_path;
	int		i;

	full_path = NULL;
	i = 0;
	while (paths[i])
	{
		full_path = build_full_command_path(paths[i], command_no_flag);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			*found = 1;
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (NULL);
}

static char	*check_direct_path(t_env_list *env, char *cmd)
{
	if (access(cmd, F_OK) != 0 || access(cmd, X_OK) != 0)
		return (perror(cmd), env->last_exit_status = 126, NULL);
	return (xalloc(ALLOC_STRDUP, cmd, NULL, 0));
}

/**
 * Returns full path of the command or NULL if not found.
 */
char	*get_command_path(t_env_list *env, char *cmd_no_flag)
{
	char	**paths;
	char	*full_path;
	int		found;

	if (!cmd_no_flag || *cmd_no_flag == '\0')
		return (NULL);
	if ((cmd_no_flag[0] == '.' && cmd_no_flag[1] == '/')
		|| cmd_no_flag[0] == '/')
		return (check_direct_path(env, cmd_no_flag));
	paths = split_path(env);
	if (!paths)
		return (NULL);
	found = 0;
	full_path = get_full_path(paths, cmd_no_flag, &found);
	free_dbl_ptr(paths);
	if (!found && full_path == NULL)
		env->last_exit_status = 127;
	return (full_path);
}
