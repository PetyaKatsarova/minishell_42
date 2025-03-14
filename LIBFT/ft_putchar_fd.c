/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 16:37:08 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/10/10 16:37:13 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//c: The character to output.
//fd: The file descriptor on which to write.
//Outputs the character ’c’ to the given file descriptor.
void	ft_putchar_fd(char d, int fd)
{
	write(fd, &d, sizeof(char));
}
