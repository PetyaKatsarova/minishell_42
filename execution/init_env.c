#include "../includes/minishell.h"

static int env_len(char **env)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    return (i);
}

// needs to change: coming from parser
/*
Returns arr of t_env structs
*/
t_env   *init_env(char **env)
{
    int     i;
    int     len;
    t_env   *env_struct;
    
    len = env_len(env);
    env_struct = malloc(sizeof(t_env) * (len + 1));
    if (!env_struct) return (NULL);

    i = 0;
    while (env[i])
    {
        char    *delim = ft_strchr(env[i], '=');
        if (!delim)
            continue;
        int key_len = delim - env[i];
        env_struct[i].key = ft_substr(env[i], 0, key_len);
        env_struct[i].value = ft_strdup(delim + 1);
        env_struct[i].exported = 1;
        i++;
    }
    env_struct[i].key = NULL;
    return (env_struct);
}

char    *get_env_value(t_env *env, const char *key)
{
	int i = 0;
	size_t len = ft_strlen(key);
	while (env[i].key)
	{
		if (ft_strncmp(env[i].key, key, len) == 0 && env[i].key[len] == '\0')
			return env[i].value;
		i++;
	}
	return NULL;
}

void set_env_value(t_env *env, const char *key, const char *val)
{
	int i = 0;
	size_t len = ft_strlen(key);
	while (env[i].key)
	{
		if (ft_strncmp(env[i].key, key, len) == 0 && env[i].key[len] == '\0')
		{
			free(env[i].value);
			env[i].value = ft_strdup(val);
			return;
		}
		i++;
	}
	// Key not found — optionally add it if needed: todo...
}

t_env   *copy_env(char **env)
{
	int i = 0;
	int count = 0;

	while (env[count])
		count++;

	t_env *env_struct = malloc(sizeof(t_env) * (count + 10)); // reserve extra room
	if (!env_struct)
		return NULL;

	for (i = 0; i < count; i++)
	{
		char *delim = ft_strchr(env[i], '=');
		if (!delim)
			continue;
		int key_len = delim - env[i];
		env_struct[i].key = ft_substr(env[i], 0, key_len);
		env_struct[i].value = ft_strdup(delim + 1);
		env_struct[i].exported = 1;
	}
	env_struct[i].key = NULL; // null-terminate
	return (env_struct);
}
