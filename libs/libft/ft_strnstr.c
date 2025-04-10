/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_strnstr.c									   :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/12 10:03:13 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/12 10:07:59 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return ((char *) haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] != '\0')
	{
		while (haystack[i + j] == needle[j] && i + j < len
			&& j < ft_strlen(needle))
			j++;
		if (ft_strlen(needle) == j)
			return ((char *) &haystack[i]);
		i++;
		j = 0;
	}
	return (NULL);
}
