/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 18:28:15 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/06 10:17:09 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_env_list *env_list, const char *key)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(key);
	while (i < env_list->size)
	{
		if (ft_strncmp(env_list->vars[i].key, key, len) == 0
			&& env_list->vars[i].key[len] == '\0')
			return (env_list->vars[i].value);
		i++;
	}
	return (NULL);
}

static int	expand_env_capacity(t_env_list *env)
{
	t_env	*new_vars;
	size_t	i;
	size_t	new_cap;

	new_cap = env->capacity * 2;
	new_vars = xalloc(
			ALLOC_MALLOC, NULL, NULL, sizeof(t_env) * new_cap);
	i = 0;
	while (i < env->size)
	{
		new_vars[i] = env->vars[i];
		i++;
	}
	free(env->vars);
	env->vars = new_vars;
	env->capacity = new_cap;
	return (0);
}

static void	set_new_env(t_env_list *env, const char *key, const char *val)
{
	env->vars[env->size].key = xalloc(
			ALLOC_STRDUP, (char *)key, NULL, 0);
	if (val)
		env->vars[env->size].value = xalloc(
				ALLOC_STRDUP, (char *)val, NULL, 0);
	else
		env->vars[env->size].value = NULL;
	env->vars[env->size].exported = 1;
	env->size++;
	env->vars[env->size].key = NULL;
}

void	set_env_value(t_env_list *env, const char *key, const char *val)
{
	size_t	i;
	size_t	len;

	if (!key || !env)
		return ;
	len = ft_strlen(key);
	i = 0;
	while (i < env->size)
	{
		if (ft_strncmp(env->vars[i].key, key, len) == 0
			&& env->vars[i].key[len] == '\0')
		{
			if (val)
			{
				free(env->vars[i].value);
				env->vars[i].value = xalloc(
						ALLOC_STRDUP, (char *)val, NULL, 0);
			}
			return ;
		}
		i++;
	}
	if (env->size + 1 >= env->capacity && expand_env_capacity(env))
		return (ft_putstr_fd("minishell: env full\n", 2));
	set_new_env(env, key, val);
}
