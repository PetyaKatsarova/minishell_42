
#include "../includes/minishell.h"

int env_len(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return i;
}


t_env_list *copy_env(char **env)
{
	int i = 0;
	int len = env_len(env);

	t_env_list *env_list = malloc(sizeof(t_env_list));
	if (!env_list)
		return NULL;

	env_list->vars = malloc(sizeof(t_env) * (len + 10));
	if (!env_list->vars)
	{
		free(env_list);
		return NULL;
	}

	env_list->size = 0;
	env_list->capacity = len + 10;
	env_list->last_exit_status = 0;

	while (env[i])
	{
		char *delim = ft_strchr(env[i], '=');
		if (!delim)
		{
			env_list->vars[env_list->size].key = ft_strdup(env[i]);
			env_list->vars[env_list->size].value = NULL;
		}
		else
		{
			int key_len = delim - env[i];
			env_list->vars[env_list->size].key = ft_substr(env[i], 0, key_len);
			env_list->vars[env_list->size].value = ft_strdup(delim + 1);
			env_list->vars[env_list->size].exported = 1;
		}
		env_list->size++;
		i++;
	}
	env_list->vars[env_list->size].key = NULL;
	return env_list;
}


char *get_env_value(t_env_list *env_list, const char *key)
{
	size_t	i;
	size_t	len;
	
	i = 0;
	len = ft_strlen(key);
	while (i < env_list->size)
	{
		if (ft_strncmp(env_list->vars[i].key, key, len) == 0 && env_list->vars[i].key[len] == '\0')
			return env_list->vars[i].value;
		i++;
	}
	return NULL;
}

static int	expand_env_capacity(t_env_list *env)
{
	t_env	*new_vars;
	size_t	i;
	size_t	new_cap;

	new_cap = env->capacity * 2;
	new_vars = malloc(sizeof(t_env) * new_cap);
	if (!new_vars)
		return (1);
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

/**
 * @brief TODO: CANT USE REALLOC
 * @details if key, updates val, if key=null, adds new key=val with malloc
	 */
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
				env->vars[i].value = ft_strdup(val);
			}
			return ;
		}
		i++;
	}
	if (env->size + 1 >= env->capacity && expand_env_capacity(env))
		return (ft_putstr_fd("minishell: env full\n", 2));
	env->vars[env->size].key = ft_strdup(key);
	env->vars[env->size].value = val ? ft_strdup(val) : NULL;
	env->vars[env->size].exported = 1;
	env->size++;
	env->vars[env->size].key = NULL;
}
	
	

/**
 * @brief Converts the env_struct to a char ** array for execve
 */
char	**converted_env(t_env_list *env_struct)
{
	char	**env;
	char	*joined;
	size_t	i;
	size_t	j;

	env = malloc(sizeof(char *) * (env_struct->size + 1));
	if (!env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < env_struct->size)
	{
		if (env_struct->vars[i].exported && env_struct->vars[i].key && env_struct->vars[i].value)
		{
			joined = ft_strjoin(env_struct->vars[i].key, "=");
			if (!joined)
				return (free_arr(env), NULL);
			env[j] = ft_strjoin(joined, env_struct->vars[i].value);
			free(joined);
			if (!env[j])
				return (free_arr(env), NULL);
			j++;
		}
		i++;
	}
	env[j] = NULL;
	return (env);
}

