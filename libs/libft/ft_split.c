/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_split.c										 :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2024/10/10 17:02:47 by pekatsar	  #+#	#+#				 */
/*   Updated: 2024/10/10 17:17:59 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

/*
s: The string to be split. c: The delimiter character.
Return : The array of new strings resulting from the split.
 NULL if the allocation fails. use malloc and FREE()
Allocates (with malloc(3)) and returns an array of strings
 obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end with a NULL pointer.
*/

#include "libft.h"

static int	ft_wordscount(const char *str, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (*str == c)
			flag = 0;
		str++;
	}
	return (count);
}

static char	*ft_worddup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word || (finish - start <= 0))
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static	char	**ft_free(char	**split, size_t j)
{
	while (j)
		free(split[--j]);
	free(split);
	return (NULL);
}

static	char	**ft_shorter(char const *s, char **split, char c)
{
	int		start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	start = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			split[j++] = ft_worddup(s, start, i);
			if (!split[j - 1])
				return (ft_free(split, j));
			start = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	split = malloc((ft_wordscount(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	return (ft_shorter(s, split, c));
}
