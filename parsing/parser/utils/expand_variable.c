/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   expand_variable.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:17:55 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:17:57 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

static char	*get_variable(char *lexeme, t_parsing_data *data)
{
	size_t	i;
	size_t	j;
	char	*var;

	i = 1;
	while (is_valid_var_char(lexeme[i]))
	{
		i++;
	}
	var = malloc((i + 1) * sizeof(char));
	if (var == NULL)
	{
		perror("get_variable(): malloc failed");
		exit_failure_parser(data);
	}
	i = 1;
	j = 0;
	while (is_valid_var_char(lexeme[i]))
	{
		var[j++] = lexeme[i++];
	}
	var[j] = '\0';
	return (var);
}

void	expand_variable(char **cpy, char **lexeme, t_parsing_data *data)
{
	char	*var;
	char	*var_val;

	var = get_variable(*lexeme, data);
	var_val = get_env_value(data->env_list, var);
	while (var_val != NULL && *var_val != '\0')
	{
		copy_char(cpy, &var_val, data);
	}
	(*lexeme)++;
	while (is_valid_var_char(**lexeme))
	{
		(*lexeme)++;
	}
	free(var);
}
