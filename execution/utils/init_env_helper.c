/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env_helper.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 18:19:07 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/02 18:50:47 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static void	another_helper(char **env, t_env_list *env_list, int key_len, int i)
{
	char	*delim;

	i = 0;
	while (env[i])
	{
		delim = ft_strchr(env[i], '=');
		if (!delim)
		{
			env_list->vars[env_list->size].key = xalloc(
					ALLOC_STRDUP, env[i], NULL, 0);
			env_list->vars[env_list->size].value = NULL;
			env_list->vars[env_list->size].exported = 0;
		}
		else
		{
			key_len = delim - env[i];
			env_list->vars[env_list->size].key = xalloc(
					ALLOC_SUBSTR, env[i], (void *)(size_t)0, key_len);
			env_list->vars[env_list->size].value = xalloc(
					ALLOC_STRDUP, delim + 1, NULL, 0);
			env_list->vars[env_list->size].exported = 1;
		}
		env_list->size++;
		i++;
	}
}

t_env_list	*copy_env(char **env)
{
	t_env_list	*env_list;
	int			len;
	int			i;
	int			key_len;

	len = env_len(env);
	i = 0;
	key_len = 0;
	env_list = xalloc(
			ALLOC_MALLOC, NULL, NULL, sizeof(t_env_list));
	env_list->vars = xalloc(
			ALLOC_MALLOC, NULL, NULL, sizeof(t_env) * (len + 10));
	env_list->size = 0;
	env_list->capacity = len + 10;
	env_list->last_exit_status = 0;
	another_helper(env, env_list, key_len, i);
	env_list->vars[env_list->size].key = NULL;
	return (env_list);
}

char	**converted_env(t_env_list *env_struct)
{
	char	**env;
	char	*joined;
	size_t	i;
	size_t	j;

	env = xalloc(ALLOC_MALLOC, NULL, NULL,
			sizeof(char *) * (env_struct->size + 1));
	i = 0;
	j = 0;
	while (i < env_struct->size)
	{
		if (env_struct->vars[i].exported
			&& env_struct->vars[i].key && env_struct->vars[i].value)
		{
			joined = xalloc(
					ALLOC_STRJOIN, env_struct->vars[i].key, "=", 0);
			env[j] = xalloc(
					ALLOC_STRJOIN, joined, env_struct->vars[i].value, 0);
			free(joined);
			j++;
		}
		i++;
	}
	env[j] = NULL;
	return (env);
}
