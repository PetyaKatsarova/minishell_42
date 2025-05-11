/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 11:34:01 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/10 12:33:41 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Frees t_tree, env_struct_list and clears history
 */
static void	free_exit_resources(t_env_list *env_struct, t_tree *tree)
{
	free_tree(tree);
	free_t_env(env_struct);
	termios_sigquit_on();
	clear_history();
}

/**
 * Frees tree, history and env_struct, prints err exit too many args
 * and exits with EXIT_FAILURE.
 */
static void	handle_too_many_args(t_env_list *env_struct, t_tree *tree)
{
	print_builtin_error("exit", NULL, "too many arguments");
	(void)env_struct;
	(void)tree;
	exit(EXIT_FAILURE);
}

/**
 * Returns 1 if the argument is a valid exit argument (numeric), 0 otherwise.
 */
static int	is_valid_exit_arg(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	write_invalid_args(t_node *cmd_node)
{
	write(STDERR_FILENO, "minisell: exit: ", 16);
	write(STDERR_FILENO, cmd_node->argv[1], ft_strlen(cmd_node->argv[1]));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	return (EXIT_INVALID_BUILTIN_ARGS);
}

/**
 * only exit typed directly (not in a pipeline) should exit your shell.
 */
int	do_exit(t_env_list *env_struct, t_tree *tree, t_node *cmd_node)
{
	int	exit_status;

	if (env_struct->last_exit_status)
		exit_status = env_struct->last_exit_status;
	else
		exit_status = 0;
	if (get_num_pipes(tree) == 0)
		write(STDERR_FILENO, "exit\n", 5);
	if (!cmd_node->argv[1])
	{
		free_exit_resources(env_struct, tree);
		exit(exit_status);
	}
	else if (cmd_node->argv[1] && is_valid_exit_arg(cmd_node->argv[1]))
	{
		if (cmd_node->argv[2])
			handle_too_many_args(env_struct, tree);
		exit_status = ft_atoi(cmd_node->argv[1]) % 256;
	}
	else if (cmd_node->argv[1])
		exit_status = write_invalid_args(cmd_node);
	free_exit_resources(env_struct, tree);
	exit(exit_status);
}
