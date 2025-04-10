/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_putendl_fd.c									:+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/10 16:37:27 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/10 16:37:30 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Outputs the string ’s’ to the given file descriptor
followed by a newline.
*/

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
