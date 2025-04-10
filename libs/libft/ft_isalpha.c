/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_isalpha.c									   :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/10 16:32:43 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/12 09:48:47 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
