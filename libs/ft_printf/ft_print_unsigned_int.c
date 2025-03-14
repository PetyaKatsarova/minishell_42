/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_unsigned_int.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/10 13:24:51 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/11/10 13:24:56 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	ft_num_len(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*ft_uitoa(unsigned int n)
{
	unsigned int	len;
	char			*str;

	len = ft_num_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
	{
		len = write(1, "0", 1);
		return (0);
	}
	while (n != 0)
	{
		str[len--] = n % 10 + 48;
		n = n / 10;
	}
	return (str);
}

int	ft_print_unsigned_int(unsigned int n)
{
	int		len;
	char	*num;

	len = 0;
	if (n == 0)
		return (write(1, "0", 1));
	num = ft_uitoa(n);
	if (num == NULL)
		return (-1);
	len = ft_printstr(num);
	free(num);
	return (len);
}
