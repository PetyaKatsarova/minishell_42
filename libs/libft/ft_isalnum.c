/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_isalnum.c									   :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/12 09:47:42 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/12 09:47:45 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((ft_isalpha(c) != 0) || (ft_isdigit(c) != 0))
		return (1);
	return (0);
}
