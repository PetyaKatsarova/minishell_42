/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_striteri.c									  :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/10 17:30:09 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/10 17:30:12 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* s: The string on which to iterate.
f: The function to apply to each character.
Descr: Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!*s || !s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
