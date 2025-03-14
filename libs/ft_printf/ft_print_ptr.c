/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_ptr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/10 13:24:30 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/11/10 13:28:11 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdint.h>

// %p The void * pointer argument has to be printed in hexadecimal format.

static int	ft_plen(uintptr_t n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

static	int	ft_to_ptr(uintptr_t n)
{
	uintptr_t	val;

	val = 0;
	if (n >= 16)
	{
		if (ft_to_ptr(n / 16) == -1)
			return (-1);
	}
	n = n % 16;
	if (n <= 9)
		val = ft_printchar((n + '0'));
	else
		val = ft_printchar((n - 10 + 'a'));
	return (val);
}

int	ft_print_ptr(unsigned long p)
{
	int	length;

	if (p == 0)
		return (write(1, "(nil)", 5));
	length = write(1, "0x", 2);
	if (length == -1)
		return (-1);
	if (p == 0)
		length += write(1, "0", 1);
	else
	{
		if (ft_to_ptr(p) == -1)
			return (-1);
		length += ft_plen(p);
	}
	return (length);
}
