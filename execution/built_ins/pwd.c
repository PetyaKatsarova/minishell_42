/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   pwd.c											  :+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/03/20 14:44:21 by pekatsar	  #+#	#+#				 */
/*   Updated: 2025/03/26 14:08:21 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_pwd(char **argv)
{
	char	buff[PATH_MAX + 1];
	size_t	len;

	if (argv && !argv[1])
	{
		if (!getcwd(buff, PATH_MAX + 1))
		{
			perror("minishell: error pwd");
			return (EXIT_FAILURE);
		}
		len = ft_strlen(buff);
		write(STDOUT_FILENO, buff, len);
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		write(STDERR_FILENO, "minisell: pwd: invalid option\n", 30);
		return (1);
	}
	return (EXIT_SUCCESS);
}
