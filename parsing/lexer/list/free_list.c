/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   free_list.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:12:09 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:12:11 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

void	free_list(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = *head;
	while (current != NULL)
	{
		if (current->lexeme != NULL)
		{
			free(current->lexeme);
		}
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}
