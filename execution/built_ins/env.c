#include "../../includes/minishell.h"

/*
!!NB!!
_=/usr/bin/env
Means the last command run was /usr/bin/env, and _ was set to that.
echo hello world
echo $_
In Bash, the special variable _ holds:
The last argument to the last executed command.
*/

int get_env(t_env_list *env)
{
    int i = 0;
    while (i < env->size)
    {
        if (env->vars[i].exported && env->vars[i].value)
            printf("%s=%s\n", env->vars[i].key, env->vars[i].value);
        i++;
    }
    return (0);
}
