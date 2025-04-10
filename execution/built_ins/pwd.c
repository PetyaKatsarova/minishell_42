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

/*
TODO: parser: handle invalid args: pwd -bla: 
pwd -bla
bash: pwd: -b: invalid option
pwd: usage: pwd [-LP]
pekatsar@f1r5s19:~$ $?
2: command not found
*/
int	get_pwd()
{
	/*
PATH_MAX is a constant defined in <limits.h> on most Unix-like systems. It specifies the maximum length of a file path, including the null-terminating character (\0). This value is used to ensure that buffers allocated for file paths are large enough to hold the longest possible path on the system.
	*/
	char	buff[PATH_MAX + 1];
	
	// copies an absolute pathname of the current working directory to the array pointed to by buf, which is of length size.
	/*
	!!   If the length of the absolute pathname of the current working directory, including the  terminating  null  byte,  exceeds  size  bytes,  NULL is returned, and errno is set to ERANGE; an application should check for this error,  and allocate a larger buffer if necessary. ---- TODO -----------------------------
	*/
	if (!getcwd(buff, PATH_MAX + 1))
	{
		perror("minishell: error pwd"); // todo: proper handle and waht to print?
		return (EXIT_FAILURE); // TODO: SET up system of err num, clean all end copy bash docomentation....
	}
	printf("%s\n", buff);
	return (EXIT_SUCCESS); // 0
}
