#include "../includes/minishell.h"



#include "../includes/minishell.h"

static int env_len(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return i;
}

t_env_list *copy_env(char **env)
{
	int		 i = 0;
	int		 len = env_len(env);
	t_env_list *env_list = malloc(sizeof(t_env_list));

	env_list->vars = malloc(sizeof(t_env) * (len + 10)); // reserve extra space **todo** is good idea? was + 10
	if (!env_list || !env_list->vars)
		return NULL;

	env_list->size = 0;
	env_list->capacity = len + 10;
	// env_list->shlvl = 1;
	env_list->is_child = 0;

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
	size_t i = 0;
	size_t len = ft_strlen(key);
	while (i < env_list->size)
	{
		if (ft_strncmp(env_list->vars[i].key, key, len) == 0 && env_list->vars[i].key[len] == '\0')
			return env_list->vars[i].value;
		i++;
	}
	return NULL;
}

void set_env_value(t_env_list *env_list, const char *key, const char *val)
{
	size_t i = 0;
	size_t len = ft_strlen(key);
	while (i < env_list->size)
	{
		if (ft_strncmp(env_list->vars[i].key, key, len) == 0 && env_list->vars[i].key[len] == '\0')
		{
			free(env_list->vars[i].value);
			env_list->vars[i].value = ft_strdup(val);
			return;
		}
		i++;
	}
	if (env_list->size >= env_list->capacity)
	{
		env_list->capacity *= 2;
		env_list->vars = realloc(env_list->vars, sizeof(t_env) * env_list->capacity);
	}
	env_list->vars[env_list->size].key = ft_strdup(key);
	env_list->vars[env_list->size].value = ft_strdup(val);
	env_list->vars[env_list->size].exported = 1;
	env_list->size++;
	env_list->vars[env_list->size].key = NULL;
}

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


void free_env_struct(t_env_list *env_struct)
{
	for (size_t i = 0; i < env_struct->size; i++)
	{
		free(env_struct->vars[i].key);
		free(env_struct->vars[i].value);
	}
	free(env_struct->vars);
	free(env_struct);
}
void free_env_list(t_env_list *env_struct)
{
	for (size_t i = 0; i < env_struct->size; i++)
	{
		free(env_struct->vars[i].key);
		free(env_struct->vars[i].value);
	}
	free(env_struct->vars);
	free(env_struct);
}
void free_env(t_env_list *env_struct)
{
	for (size_t i = 0; i < env_struct->size; i++)
	{
		free(env_struct->vars[i].key);
		free(env_struct->vars[i].value);
	}
	free(env_struct->vars);
	free(env_struct);
}
