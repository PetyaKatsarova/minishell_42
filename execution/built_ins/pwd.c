/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/20 14:44:21 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/26 14:08:21 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_pwd()
{
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
