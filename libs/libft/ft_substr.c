/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/12 10:03:13 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/10/12 10:08:16 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mysub;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	if (s_len < start + len)
	{
		mysub = ft_calloc((s_len - start + 1), sizeof(char));
		if (!mysub)
			return (NULL);
		ft_strlcpy(mysub, (s + start), (s_len - start + 1));
		return (mysub);
	}
	mysub = ft_calloc(len + 1, sizeof(char));
	if (!mysub)
		return (NULL);
	ft_strlcpy(mysub, s + start, len + 1);
	return (mysub);
}
