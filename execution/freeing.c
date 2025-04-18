#include "../includes/minishell.h"

/**
 * @brief if arr is NULL, do nothing. Otherwise, free each string in arr and then free arr itself.
 */
void free_arr(char **arr)
{
	size_t	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
/**
 * Frees t_env_list, protects if key, val or list is null
 */
//void free_t_env(t_env_list *env_struct)
//{
//	size_t i = 0;
//	while (i < env_struct->size)
//	{
//		free(env_struct->vars[i].key);
//		if (env_struct->vars[i].value)
//			free(env_struct->vars[i].value);
//		i++;
//	}
//	free(env_struct->vars);
//	free(env_struct);
//}
void	free_t_env(t_env_list *env_struct)
{
	size_t	i;

	if (!env_struct || !env_struct->vars)
		return;
	i = 0;
	while (i < env_struct->size)
	{
		if (env_struct->vars[i].key)
			free(env_struct->vars[i].key);
		if (env_struct->vars[i].value)
			free(env_struct->vars[i].value);
		i++;
	}
	free(env_struct->vars);
	free(env_struct);
}

