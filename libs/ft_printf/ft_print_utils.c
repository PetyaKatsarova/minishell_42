/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/10 13:25:04 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/11/10 13:25:08 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printchar(int c)
{
	return (write(1, &c, sizeof(char)));
}

int	ft_printperc(void)
{
	return (write(1, "%", 1));
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		if (write (1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	else
	{
		i = ft_strlen(str);
		if (write(1, str, i) == -1)
			return (-1);
	}
	return (i);
}

int	ft_num_len(unsigned int n)
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
