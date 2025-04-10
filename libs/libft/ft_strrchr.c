/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_strrchr.c									   :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/12 10:03:13 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/12 10:08:05 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*temp;

	temp = (char *)s;
	i = ft_strlen(temp);
	while (i > -1)
	{
		if (temp[i] != (char)c)
			i--;
		else
			return (&temp[i]);
	}
	return (NULL);
}
