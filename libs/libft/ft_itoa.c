/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_itoa.c										  :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/10 16:32:43 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/12 09:50:59 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

static	int	ft_nlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		length;

	length = ft_nlen(n);
	str = (char *) ft_calloc(sizeof(char), (length + 1));
	if (!str)
		return (NULL);
	str[length--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	while (n != 0)
	{
		if (str[0] == '-')
			str[length--] = '0' - (n % 10);
		else
		{
			str[length] = '0' + (n % 10);
			length--;
		}
		n = n / 10;
	}
	return (str);
}
