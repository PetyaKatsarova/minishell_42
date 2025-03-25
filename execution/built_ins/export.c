/*
Input	What to do
VAR=value	Add to list (not exported)
export VAR	Mark as exported (even if it had no value yet)
export VAR=hi	Add/update and mark exported
env	Print only exported + with values
export	Print all (with or without value), format as declare -x

VAR1=hello          # just stored, not exported
export VAR1         # now it's exported
env                 # now shows VAR1=hello
export              # shows declare -x VAR1="hello"
*/
#include "../../includes/minishell.h"

int do_export(char **input_args, t_env *env_struct)
{
    int     i;
    char    *delim;

    if (!input_args[1])
    {
        i = 0;
        while (env_struct[i].key)
        {
            printf("declare -x %s", env_struct[i].key);
            if (env_struct[i].value)
                printf("=\"%s\"", env_struct[i].value);
            printf("\n");
            i++;
        }
        return (0);
    }
    i = 1;
    while (input_args[i])
    {
        delim = ft_strchr(input_args[i], '=');
        if (delim)
        {
            int     key_len = delim - input_args[i];
            char    *key = ft_substr(input_args[i], 0, key_len);
            char    *val = ft_strdup(delim + 1);
            set_env_value(env_struct, key, val);
            free(key);
            free(val); 
        }
        else
        {
            set_export_flag(env_struct, input_args[i]);
        }
        i++;
    }
    return (0);
}
