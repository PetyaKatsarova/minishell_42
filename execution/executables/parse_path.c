/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 11:20:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/18 17:42:33 by pekatsar      ########   odam.nl         */
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
	{
		perror("Error in converting env.");
		return (NULL);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			arr = ft_split(env[i] + 5, ':');
			free_arr(env);
			if (!arr)
			{
				perror("Error in splitting PATH.");
				free_arr(env);
				return (NULL);
			}
			return (arr);
		}
		i++;
	}
	perror("PATH not found in env.");
	free_arr(env);
	return (NULL);
}

static char	*build_full_command_path(char *path, char *command_no_flag)
{
	char	*with_line;
	char	*full_path;

	with_line = ft_strjoin(path, "/");
	if (!with_line)
	{
		perror("ft_strjoin with_line failed");
		return (NULL);
	}
	full_path = ft_strjoin(with_line, command_no_flag);
	free(with_line);
	if (!full_path)
		perror("ft_strjoin full_path failed");
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

char	*get_command_path(t_env_list *env, char *cmd_no_flag)
{
	char	**paths;
	char	*full_path;
	int		found;

	if (ft_strlen(cmd_no_flag) == 0)
		return (NULL);
	if ((cmd_no_flag[0] == '.' && cmd_no_flag[1] == '/')
		|| cmd_no_flag[0] == '/')
	{
		if (is_valid_read_or_exec_file(cmd_no_flag, 'x'))
			return (ft_strdup(cmd_no_flag));
		else
		{
			return (NULL);
		}
	}
	//paths = split_and_validate_paths(env);
	paths = split_path(env);
	if (!paths)
		return (NULL);
	found = 0;
	full_path = get_full_path(paths, cmd_no_flag, &found);
	free_dbl_ptr(paths);
	if (found)
		return (full_path);
	return (NULL);
}
