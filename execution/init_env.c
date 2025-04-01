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
    int         i = 0;
    int         len = env_len(env);
    t_env_list *env_list = malloc(sizeof(t_env_list));

    env_list->vars = malloc(sizeof(t_env) * (len + 10)); // reserve extra space
    if (!env_list || !env_list->vars)
        return NULL;

    env_list->size = 0;
    env_list->capacity = len + 10;

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
    int i = 0;
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
    int i = 0;
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

void unset_export_flag(t_env_list *env_list, const char *key)
{
    int     i;
    size_t  key_len = ft_strlen(key);

    for (i = 0; i < env_list->size; i++)
    {
        if (ft_strncmp(env_list->vars[i].key, key, key_len) == 0 &&
            env_list->vars[i].key[key_len] == '\0' && key[key_len] == '\0')
        {
            env_list->vars[i].exported = 0;
            return;
        }
    }
    if (env_list->size >= env_list->capacity)
    {
        env_list->capacity *= 2;
        env_list->vars = realloc(env_list->vars, sizeof(t_env) * env_list->capacity);
    }
    env_list->vars[env_list->size].key = ft_strdup(key);
    env_list->vars[env_list->size].value = NULL;
    env_list->vars[env_list->size].exported = 1;
    env_list->size++;
    env_list->vars[env_list->size].key = NULL;
}




// int env_len(char **env)
// {
//     int i;

//     i = 0;
//     while (env[i])
//         i++;
//     return (i);
// }

// // needs to change: coming from parser
// /*
// Returns arr of t_env structs
// */
// t_env   *copy_env(char **env)
// {
//     int     i;
//     int     len;
//     t_env   *env_struct;
    
//     len = env_len(env);
//     env_struct = malloc(sizeof(t_env) * (len + 1));
//     if (!env_struct) return (NULL);

//     i = 0;
//     while (env[i])
//     {
//         char    *delim = ft_strchr(env[i], '=');
//         if (!delim)
//             continue;
//         int key_len = delim - env[i];
//         env_struct[i].key = ft_substr(env[i], 0, key_len);
//         env_struct[i].value = ft_strdup(delim + 1); // protect ehre with checks!! TODO and abv too
//         env_struct[i].exported = 1;
// 		//printf("init: %s=%s\n", env_struct[i].key, env_struct->value);
//         i++;
//     }
//     env_struct[i].key = NULL;
//     return (env_struct);
// }

// char    *get_env_value(t_env *env, const char *key)
// {
// 	int i = 0;
// 	size_t len = ft_strlen(key);
// 	while (env[i].key)
// 	{
// 		if (ft_strncmp(env[i].key, key, len) == 0 && env[i].key[len] == '\0')
// 			return env[i].value;
// 		i++;
// 	}
// 	return NULL;
// }

// void set_env_value(t_env *env, const char *key, const char *val)
// {
// 	int i = 0;
// 	size_t len = ft_strlen(key);
// 	while (env[i].key)
// 	{
// 		if (ft_strncmp(env[i].key, key, len) == 0 && env[i].key[len] == '\0')
// 		{
// 			free(env[i].value);
// 			env[i].value = ft_strdup(val);
// 			return;
// 		}
// 		i++;
// 	}
// 	// Key not found — optionally add it if needed: todo...
// }
// // TODO : THE LOGIC IS WRONG, TO FIX
// void unset_export_flag(t_env *env_struct, const char *key)
// {
//     int     i;
//     size_t  key_len;

//     i = 0;
//     key_len = ft_strlen(key);
//     while (env_struct[i].key)
//     {
//         if (ft_strncmp(env_struct[i].key, key, key_len) == 0 &&
// 		    env_struct[i].key[key_len] == '\0' &&
// 		    key[key_len] == '\0')
// 		{
// 			env_struct[i].exported = 0;
// 			return;
// 		}
// 		i++;
//     }

//     // add new key with null val and exported=1
//     i = 0;
//     while (env_struct[i].key)
//         i++;
//     env_struct[i].key = ft_strdup(key);
//     env_struct[i].value = NULL;
//     env_struct[i].exported = 1;
//     env_struct[i+1].key = NULL; // todo: did we add 10 extra spaces, just in case? or is it dynamically allocated?
// }