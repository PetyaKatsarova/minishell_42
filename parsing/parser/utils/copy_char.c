/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   copy_char.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:17:08 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:17:11 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

void	copy_char(char **target, char **source, t_parsing_data *data)
{
	**target = **source;
	(*target)++;
	(*source)++;
	if ((size_t)(*target - data->new) >= data->size - 1)
	{
		data->new = reallocate_str(data->new, data);
		*target = data->new;
		while (**target != '\0')
		{
			(*target)++;
		}
	}
}
