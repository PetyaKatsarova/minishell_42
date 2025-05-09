/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   expand.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/06 13:56:54 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/06 13:56:55 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"
#include "../../../includes/minishell.h"

void	expand(char **cpy, char **lexeme, t_parsing_data *data)
{
	if (*(*lexeme + 1) == '?')
	{
		expand_exit_status(cpy, lexeme, data);
	}
	else if (is_valid_var_char(*(*lexeme + 1)) == false)
	{
		copy_char(cpy, lexeme, data);
	}
	else
	{
		expand_variable(cpy, lexeme, data);
	}
}
