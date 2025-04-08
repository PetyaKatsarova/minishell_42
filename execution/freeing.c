#include "../includes/minishell.h"

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

// needs to change: coming from parser
/*
Returns arr of t_env structs
*/
void free_t_env(t_env_list *env_struct)
{
    int i = 0;
    while (i < env_struct->size)
    {
        free(env_struct->vars[i].key);
        if (env_struct->vars[i].value)
            free(env_struct->vars[i].value);
        i++;
    }
    free(env_struct->vars);
    free(env_struct);
}
