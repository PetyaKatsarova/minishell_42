/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_putnbr_fd.c									 :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/10 16:38:05 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/10 16:58:04 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

//n: The integer to output.
// fd: The file descriptor on which to write.
//Outputs the integer ’n’ to the given file descriptor
void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (nb < 0)
		{
			ft_putchar_fd('-', fd);
			nb = nb * (-1);
		}
		if (nb > 9)
			ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd((nb % 10 + '0'), fd);
	}
}
