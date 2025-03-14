/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 17:17:41 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/10/10 17:17:53 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*chr;

	chr = (char *)s;
	while (*chr != (char)c)
	{
		if (!*chr)
			return (0);
		chr++;
	}
	return (chr);
}
