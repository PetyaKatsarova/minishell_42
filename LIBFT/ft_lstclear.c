/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/12 09:56:26 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/10/12 10:02:56 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* lst: The address of a pointer to a node.
   del: The address of the function used to delete the content of the node.
    Descr: Deletes and frees the given node and every
    successor of that node, using the function ’del’ and free(3).
    Finally, the pointer to the list must be set to\NULL.
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}
