#include "../../includes/minishell.h"

void get_env(t_env  *env)
{
    int i = 0;
    while (env[i++].key)
        printf("get-env: %s=%s\n", env[i].key, env[i].value);
}