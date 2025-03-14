/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_num.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/10 13:23:57 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/11/10 13:24:00 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_print_num(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	if (num == NULL)
		return (-1);
	len = ft_printstr(num);
	free(num);
	return (len);
}
