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

int get_env(t_env  *env)
{
    int i = 0;
    while (env[i++].key) //env[i].exported &&
        printf("%s=%s\n", env[i].key, env[i].value);
    return (0);
}