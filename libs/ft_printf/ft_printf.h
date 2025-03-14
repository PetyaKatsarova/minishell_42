/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/10 13:25:27 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/11/10 14:43:32 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

int				ft_printchar(int c);
int				ft_printstr(char *str);
int				ft_printperc(void);
int				ft_print_num(int n);
int				ft_print_unsigned_int(unsigned int n);
unsigned int	ft_print_hex(unsigned int n, const char format);
int				ft_print_ptr(unsigned long p);
int				ft_printf(const char *format, ...);

#endif