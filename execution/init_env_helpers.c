// #include "../includes/minishell.h"

// void free_env_entry(t_env *entry)
// {
// 	if (entry->key)
// 		free(entry->key);
// 	if (entry->value)
// 		free(entry->value);
// 	entry->key = NULL;
// 	entry->value = NULL;
// }

// /**
//  * Initialize a t_env entry safely.
//  * Sets pointers to NULL and exported to false.
//  */
// static void init_env_entry(t_env *entry)
// {
// 	if (!entry)
// 		return;
// 	entry->key = NULL;
// 	entry->value = NULL;
// 	entry->exported = 0;
// }

// static void and_another_free(t_env_list *env_list)
// {
//     while (env_list->size > 0)
//         free_env_entry(&env_list->vars[--env_list->size]);
//     free(env_list->vars);
//     free(env_list);
// }


// static int copy_single_env_entry(t_env *var, const char *env_str)
// {
// 	char *delim = ft_strchr(env_str, '=');
// 	int key_len;

//     init_env_entry(var);
// 	if (!delim)
// 	{
// 		var->key = ft_strdup(env_str);
// 		if (!var->key)
//             return (perror("minisell: malloc failed"), EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		key_len = delim - env_str;
// 		var->key = ft_substr(env_str, 0, key_len);
// 		if (!var->key)
//             return (perror("minisell: malloc failed"), EXIT_FAILURE);
// 		var->value = ft_strdup(delim + 1);
// 		if (!var->value)
// 		{
// 			free(var->key);
//             return (perror("minisell: malloc failed"), EXIT_FAILURE);
// 		}
// 		var->exported = 1;
// 	}
// 	return (EXIT_SUCCESS);
// }

// t_env_list *copy_env(char **env)
// {
// 	int i;
//     int len;
//     t_env_list *env_list;
    
//     i = 0;
//     len = env_len(env);
// 	env_list = malloc(sizeof(t_env_list));
// 	if (!env_list)
//         return (perror("minisell: malloc failed"), NULL);
// 	env_list->vars = malloc(sizeof(t_env) * (len + 10));
// 	if (!env_list->vars)
// 		return (free(env_list), perror("minisell: malloc failed"),NULL);
// 	env_list->size = 0;
// 	env_list->capacity = len + 10;
// 	env_list->last_exit_status = 0;
// 	while (env[i])
// 	{
// 		if (!copy_single_env_entry(&env_list->vars[env_list->size], env[i]))
//             return (and_another_free(env_list), NULL);
// 		env_list->size++;
// 		i++;
// 	}
// 	env_list->vars[env_list->size].key = NULL;
// 	return env_list;
// }
