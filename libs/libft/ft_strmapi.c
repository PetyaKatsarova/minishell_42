/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_strmapi.c									   :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/12 10:03:13 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/12 10:07:48 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* s: The string on which to iterate.
f: The function to apply to each character.
Return v: The string created from the successive applications
of ’f’.Returns NULL if the allocation fails.
Descr: Applies the function ’f’ to each character of the
string ’s’, and passing its index as first argument
to create a new string (with malloc(3)) resulting
from successive applications of ’f’.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		s_len;
	char	*str;
	int		i;

	s_len = ft_strlen(s);
	i = 0;
	str = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
