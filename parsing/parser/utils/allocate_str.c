/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   allocate_str.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:16:52 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:16:54 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

char	*allocate_str(t_parsing_data *data)
{
	char	*str;
	char	*cpy;

	str = malloc((data->size) * sizeof(char));
	if (str == NULL)
	{
		exit_failure_parser(data);
	}
	cpy = str;
	while ((size_t)(cpy - str) < data->size)
	{
		*cpy = '\0';
		cpy++;
	}
	return (str);
}
