/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   utils.c											:+:	:+:			*/
/*													 +:+					*/
/*   By: pekatsar <pekatsar@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/04/01 17:31:20 by pekatsar	  #+#	#+#				 */
/*   Updated: 2025/04/08 17:18:01 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Check if the number of arguments is more than 2.
 * 
 * @param input_args The array of arguments.
 * @return int Returns 1 if more than 2 args, 0 on 2 args.
 * 
 * This function checks if the number of arguments in the input_args array
 * is more than 2. If it is, it returns 1; otherwise, it returns 0.
 */
int	too_many_args(char	**input_args)
{
	int	i = 0;
	while (input_args[i])
		i++;
	if (i > 2)
		return (1);
	return (0);
}
/**
 * todo::: replace everywhere printf with write: ft_putstr_fd("minihell: ", 2);
 * Returns EXIT_FAILURE and prints err msg for cmd with args
 */
int	print_builtin_error(const char *cmd, const char *arg, const char *msg)
{
	if (msg)
	{
		if (arg)
		{
			printf("minishell: %s: %s: %s\n", cmd, arg, msg);
			return (EXIT_FAILURE);
		}
		printf("minishell: %s: %s\n", cmd, msg);
		return (EXIT_FAILURE);
	}
	if (arg)
	{
		printf("minishell: %s: %s: unknown error\n", cmd, arg);
		return (EXIT_FAILURE);
	}
	printf("minishell: %s: unknown error\n", cmd);
	return (EXIT_FAILURE);
}

//long	ft_atol(const char *str)
//{
//	long	result;
//	int		sign;

//	result = 0;
//	sign = 1;
//	while (*str == ' ' || (*str >= 9 && *str <= 13))
//		str++;
//	if (*str == '-' || *str == '+') // Handle sign
//	{
//		if (*str == '-')
//			sign = -1;
//		str++;
//	}
//	while (*str && *str >= '0' && *str <= '9')
//	{
//		result = result * 10 + (*str - '0');
//		str++;
//	}
//	return (result * sign);
//}
