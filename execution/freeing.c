#include "../includes/minishell.h"

void free_arr(char **arr)
{
    int i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

// needs to change: coming from parser
/*
Returns arr of t_env structs
*/
void    free_t_env(t_env *env_struct)
{
    int i;

    i = 0;
    while (env_struct[i].key)
    {
        free(env_struct[i].key);
        free(env_struct[i].value);
        i++;
    }
    free(env_struct);
}