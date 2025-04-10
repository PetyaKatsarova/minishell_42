/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strchr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: petya <petya@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/10 17:17:41 by pekatsar		  #+#	#+#			 */
/*   Updated: 2025/03/25 14:57:26 by petya			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

/*
Returns pointer to the first occurence of char c in char *str
*/
char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != (char)c)
	{
		if (!*str)
			return (0);
		str++;
	}
	return (str);
}
