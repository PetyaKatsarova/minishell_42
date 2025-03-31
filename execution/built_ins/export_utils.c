/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/28 20:09:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/31 19:01:08 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Returns malloc'ed sorted copy of env_struct
// Performs deep copy of key/value pairs
// Bubble sort by key

#include "../../includes/minishell.h"

int get_env_struct_len(t_env_list *env_struct)
{
    return env_struct->size;
}

// Returns malloc'ed sorted copy of env_struct
// Performs deep copy of key/value pairs
// Bubble sort by key

t_env_list *sort_env(t_env_list *env_struct)
{
    int i, j;
    t_env temp;
    t_env_list *cpy = malloc(sizeof(t_env_list));
    if (!cpy)
        return NULL;

    cpy->size = env_struct->size;
    cpy->capacity = env_struct->size;
    cpy->vars = malloc(sizeof(t_env) * (cpy->size + 1));
    if (!cpy->vars)
    {
        free(cpy);
        return NULL;
    }

    i = 0;
    while (i < cpy->size)
    {
        cpy->vars[i].key = ft_strdup(env_struct->vars[i].key);
        cpy->vars[i].value = env_struct->vars[i].value ? ft_strdup(env_struct->vars[i].value) : NULL;
        cpy->vars[i].exported = env_struct->vars[i].exported;
        i++;
    }
    cpy->vars[i].key = NULL;

    i = 0;
    while (i < cpy->size)
    {
        j = i + 1;
        while (j < cpy->size)
        {
            if (ft_strncmp(cpy->vars[i].key, cpy->vars[j].key, 1024) > 0)
            {
                temp = cpy->vars[i];
                cpy->vars[i] = cpy->vars[j];
                cpy->vars[j] = temp;
            }
            j++;
        }
        i++;
    }
    return cpy;
}

void print_env_export(t_env_list *env_struct)
{
    int i = 0;
    while (i < env_struct->size)
    {
        if (env_struct->vars[i].exported)
        {
            printf("declare -x %s", env_struct->vars[i].key);
            if (env_struct->vars[i].value)
                printf("=\"%s\"", env_struct->vars[i].value);
            printf("\n");
        }
        i++;
    }
}





// #include "../../includes/minishell.h"

// int	get_env_struct_len(t_env *env_struct)
// {
//     int i;

//     i = 0;
//     while (env_struct[i].key)
//         i++;
//     return (i);
// }
// /*
// Returns mallocced sorted cpy of t_env *env_struct
// */
// t_env *sort_env(t_env *env_struct)
// {
//     int     envlen;
//     t_env   *cpy_env;
//     int     i;
//     int     j;
//     t_env   temp;

//     envlen = get_env_struct_len(env_struct);
//     cpy_env = malloc(sizeof(t_env) * (envlen + 1));
//     if (!cpy_env) return (NULL);
//     i = 0;
//     while (i < envlen)
//     {
//         cpy_env[i] = env_struct[i];  // shallow copy: 
//         i++;
//     }
//     cpy_env[i].key = NULL;
//     //cpy_env[i].value = NULL;
//     i = 0;
//     while (cpy_env[i].key)
//     {
//         j = i;
//         while (cpy_env[j].key)
//         {
//             if (ft_strncmp(cpy_env[i].key, cpy_env[j].key, 2) > 0)
//             {
//                 temp = cpy_env[i];
//                 cpy_env[i] = cpy_env[j];
//                 cpy_env[j] = temp;
//             }
//             j++;
//         }
//         i++;
//     }
//     return (cpy_env);
// }

// /*
// Prints empty vars, s well
// */
// void print_env_export(t_env *sorted_env_struct)
// {
//     int i;

//     i = 0;
//     while (sorted_env_struct[i].key)
//     {
//         printf("declare -x %s=", sorted_env_struct[i].key);
//         if (sorted_env_struct[i].value)
//             printf("%s", sorted_env_struct[i].value);
//         printf("\n");
//         i++;
//     }
// }