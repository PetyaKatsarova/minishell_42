/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_lstdelone.c									 :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/12 10:03:13 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/12 10:03:20 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* lst: The node to free. del: The address of the function used
	 to delete the content.
	Descr: Takes as a parameter a node and frees the memory of
	the node’s content using the function ’del’ given
	as a parameter and free the node. The memory of
	’next’ must not be freed. use free()
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del || !lst)
		return ;
	(*del)(lst->content);
	free(lst);
}
