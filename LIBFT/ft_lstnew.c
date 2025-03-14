/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/12 10:03:13 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/10/12 10:04:41 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* content: The content to create the node with. 
Return val: the new node, use malloc
Descr: Allocates (with malloc(3)) and returns a new node.
The member variable ’content’ is initialized with
the value of the parameter ’content’. The variable
’next’ is initialized to NULL.
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*newls;

	newls = (t_list *) malloc(sizeof (*newls));
	if (!newls)
		return (NULL);
	newls->content = content;
	newls->next = NULL;
	return (newls);
}
