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
 * Frees t_env_list, checks if !envstrct || !env_struct->vars, if so, return.
 */
void	free_t_env(t_env_list *env_struct)
{
	size_t	i;

	if (!env_struct || !env_struct->vars)
		return;

	i = 0;
	while (i < env_struct->size)
	{
		if (env_struct->vars[i].key)
		{
			free(env_struct->vars[i].key);
			env_struct->vars[i].key = NULL;
		}
		if (env_struct->vars[i].value)
		{
			free(env_struct->vars[i].value);
			env_struct->vars[i].value = NULL;
		}
		i++;
	}
	free(env_struct->vars);
	env_struct->vars = NULL;

	free(env_struct);
}


