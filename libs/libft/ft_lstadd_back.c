/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_lstadd_back.c								   :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/12 09:53:19 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/12 09:53:21 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"
/* lst: The address of a pointer to the first link of a list.
   new: The address of a pointer to the node to be added to the list.
	Descr: Adds the node ’new’ at the end of the list.
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
