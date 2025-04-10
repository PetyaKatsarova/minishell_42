/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_strlcat.c									   :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/10 17:33:00 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/10 17:33:03 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dstsize < dst_len)
		return (dstsize + src_len);
	if (dstsize == 0)
		return (src_len);
	while (src[i] != '\0' && (i + dst_len) < (dstsize - 1))
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = '\0';
	return (dst_len + src_len);
}
