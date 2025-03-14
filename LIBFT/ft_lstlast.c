/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/12 10:03:13 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/10/12 10:04:09 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* lst: The beginning of the list.
	Return v: Last node of the list , i will use: int	ft_lstsize(t_list *lst)
*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*copy;

	copy = lst;
	while (copy)
	{
		if (!copy->next)
			return (copy);
		copy = copy->next;
	}
	return (copy);
}
