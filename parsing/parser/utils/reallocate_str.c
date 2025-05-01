/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   reallocate_str.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:18:51 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:18:52 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

char	*reallocate_str(char *str, t_parsing_data *data)
{
	char	*orig;
	char	*new;
	char	*cpy;

	data->size = data->size * 2;
	new = allocate_str(data);
	cpy = new;
	orig = str;
	while (*str)
	{
		*cpy = *str;
		cpy++;
		str++;
	}
	free(orig);
	return (new);
}
