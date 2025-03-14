/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/12 10:03:13 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/10/12 10:05:20 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copy byte string
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!len || dst == src)
		return (dst);
	if (src > dst)
		ft_memcpy(dst, src, len);
	else
	{
		while (len > 0)
		{
			((char *)dst)[len - 1] = ((char *)src)[len - 1];
			len--;
		}
	}
	return (dst);
}
