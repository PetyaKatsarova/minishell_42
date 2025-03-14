/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 17:31:25 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/10/10 17:31:27 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*mystr;

	i = 0;
	j = 0;
	mystr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!mystr)
		return (NULL);
	while (s1[i] != '\0')
	{
		mystr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		mystr[i + j] = s2[j];
		j++;
	}
	mystr[i + j] = '\0';
	return (mystr);
}
