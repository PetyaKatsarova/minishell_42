/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_hex.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/10 13:23:26 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/11/10 13:23:29 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
//0xABC

static int	ft_hex_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != '\0')
	{
		len++;
		num = num / 16;
	}
	return (len);
}

static int	ft_to_hex(unsigned int n, const char format)
{
	unsigned int	val;

	val = 0;
	if (n >= 16)
	{
		if (ft_to_hex(n / 16, format) == -1)
			return (-1);
	}
	n = n % 16;
	if (n <= 9)
		val = ft_printchar((n + '0'));
	else
	{
		if (format == 'x')
			val = ft_printchar((n - 10 + 'a'));
		if (format == 'X')
			val = ft_printchar((n - 10 + 'A'));
	}
	return (val);
}

unsigned	int	ft_print_hex(unsigned int n, const char format)
{
	if (n == 0)
		return (write(1, "0", 1));
	else
	{
		if (ft_to_hex(n, format) == -1)
			return (-1);
	}
	return (ft_hex_len(n));
}
