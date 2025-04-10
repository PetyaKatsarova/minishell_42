/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_strtrim.c									   :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/12 10:03:13 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/12 10:08:11 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isinset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		start;
	size_t		end;
	char		*trimmed;

	start = 0;
	while (s1[start] != '\0' && ft_isinset(s1[start], set) != 0)
		start++;
	end = ft_strlen(s1);
	while (start < end && ft_isinset(s1[end - 1], set) != 0)
		end--;
	trimmed = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start < end)
		trimmed[i++] = s1[start++];
	trimmed[i] = '\0';
	return (trimmed);
}
