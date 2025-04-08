/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/28 20:09:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/08 19:35:46 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Returns malloc'ed sorted copy of env_struct
// Performs deep copy of key/value pairs
// Bubble sort by key

#include "../../includes/minishell.h"

// Returns malloc'ed sorted copy of env_struct
// Performs deep copy of key/value pairs
// Bubble sort by key

t_env_list *sort_env(t_env_list *env_struct)
{
    size_t i, j;
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
    size_t i;

    if (!env_struct || !env_struct->vars)
        return;

    i = 0;
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
