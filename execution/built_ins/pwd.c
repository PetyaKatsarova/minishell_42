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
	if (argv && !argv[1])
	{
		if (!getcwd(buff, PATH_MAX + 1))
		{
			perror("minishell: error pwd");
			return (EXIT_FAILURE);
		}
		printf("%s\n", buff);
	}
	else
	{
		write(STDERR_FILENO, "minihell: pwd: invalid option\n", 30);
		return (1);
	}

	return (EXIT_SUCCESS);
}
