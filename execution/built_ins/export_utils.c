/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   export_utils.c									 :+:	:+:			*/
/*													 +:+					*/
/*   By: marvin <marvin@student.42.fr>				+#+					 */
/*												   +#+					  */
/*   Created: 2025/03/28 20:09:34 by pekatsar	  #+#	#+#				 */
/*   Updated: 2025/04/09 19:18:03 by anonymous	 ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void helper_sort(t_env_list *cpy, t_env_list *env_struct, int i)
{
		if (!cpy->vars[i].key)
			err_malloc(cpy, "minishell: malloc failed");
		if (env_struct->vars[i].value)
			cpy->vars[i].value = ft_strdup(env_struct->vars[i].value); // protect the strdup: todo....
		else
			cpy->vars[i].value = NULL;
		if (env_struct->vars[i].value && !cpy->vars[i].value)
			err_malloc(cpy, "minishell: malloc failed");
		cpy->vars[i].exported = env_struct->vars[i].exported;
}

t_env_list *cpy_env_list(t_env_list *env_struct)
{
	size_t	  i;
	t_env_list  *cpy;

	cpy = malloc(sizeof(t_env_list));
	if (!cpy)
		err_malloc(NULL, "minishell: malloc failed");
	cpy->size = env_struct->size;
	cpy->capacity = env_struct->size;
	cpy->vars = malloc(sizeof(t_env) * (cpy->size + 1));
	if (!cpy->vars)
		err_malloc(cpy, "minishell: malloc failed");
	i = 0;
	while (i < cpy->size)
	{
		cpy->vars[i].key = ft_strdup(env_struct->vars[i].key);
		helper_sort(cpy, env_struct, i);
		i++;
	}
	cpy->vars[i].key = NULL;
	return cpy;
}

static void sort_env_list_helper(t_env_list *cpy)
{
	size_t  i;
	size_t  j;
	t_env   temp;

	if (!cpy || !cpy->vars)
		err_malloc(NULL, "minishell: invalid t_env_list");
	i = 0;
	while (i < cpy->size)
	{
		j = i + 1;
		while (j < cpy->size)
		{
			if (ft_strncmp(cpy->vars[i].key, cpy->vars[j].key, 1024) > 0) // todo: better with ftstrlen
			{
				temp = cpy->vars[i];
				cpy->vars[i] = cpy->vars[j];
				cpy->vars[j] = temp;
			}
			j++;
		}
		i++;
	}
}

t_env_list *sort_env(t_env_list *sorted_env_struct)
{
	t_env_list *cpy;

	cpy = cpy_env_list(sorted_env_struct);
	if (!cpy)
		err_malloc(NULL, "minishell: failed to copy t_env_list");
	sort_env_list_helper(cpy);
	return cpy;
}

void print_env_export(t_env_list *env_struct)
{
	size_t i;

	if (!env_struct || !env_struct->vars)
		return; // TODO: handle error, do i?

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
