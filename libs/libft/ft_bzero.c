/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_bzero.c										 :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/12 09:47:03 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/12 09:47:21 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"
// write n seroed bytes(aka '\0') to the str s, if n==0: do nth

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (n > i)
		((unsigned char *)s)[i++] = '\0';
}
