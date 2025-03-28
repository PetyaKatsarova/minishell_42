/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/28 20:09:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/28 20:10:45 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_struct_len(t_env *env_struct)
{
    int i;

    i = 0;
    while (env_struct[i].key)
        i++;
    return (i);
}
/*
Returns mallocced sorted cpy of t_env *env_struct
*/
t_env *sort_env(t_env *env_struct)
{
    int     envlen;
    t_env   *cpy_env;
    int     i;
    int     j;
    t_env   temp;

    envlen = get_env_struct_len(env_struct);
    cpy_env = malloc(sizeof(t_env) * (envlen + 1));
    if (!cpy_env) return (NULL);
    i = 0;
    while (i < envlen)
    {
        cpy_env[i] = env_struct[i];  // shallow copy: 
        i++;
    }
    cpy_env[i].key = NULL;
    //cpy_env[i].value = NULL;
    i = 0;
    while (cpy_env[i].key)
    {
        j = i;
        while (cpy_env[j].key)
        {
            if (ft_strncmp(cpy_env[i].key, cpy_env[j].key, 2) > 0)
            {
                temp = cpy_env[i];
                cpy_env[i] = cpy_env[j];
                cpy_env[j] = temp;
            }
            j++;
        }
        i++;
    }
    return (cpy_env);
}

/*
Prints empty vars, s well
*/
void print_env_export(t_env *sorted_env_struct)
{
    int i;

    i = 0;
    while (sorted_env_struct[i].key)
    {
        printf("declare -x %s=", sorted_env_struct[i].key);
        if (sorted_env_struct[i].value)
            printf("%s", sorted_env_struct[i].value);
        printf("\n");
        i++;
    }
}