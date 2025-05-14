/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:23:34 by pekatsar          #+#    #+#             */
/*   Updated: 2025/05/14 20:39:23 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signum = 0;

static void handle_input(char *input, t_env_list *env_struct_lst)
{
	int	last_exit_status;
	
	last_exit_status = env_struct_lst->last_exit_status;
	if (!input)
	{
		write(1, "exit\n", 5);
		clear_history();
		free_t_env(env_struct_lst);
		exit(last_exit_status);
	}
	if (*input)
		add_history(input);
}

static int	handle_parsing(t_tree **tree, char **input, t_env_list *env_list)
{
	t_token	*token_list;
	
	token_list = NULL;
	if (pre_tokenization_syn_check(*input, env_list) != 0)
		return (2);
	lexer(&token_list, *input, env_list);
	if (post_tokenization_syn_check(token_list, env_list) != 0)
		return (free_list(&token_list), 2);
	*tree = treenew(token_list, env_list, *input);
	parser(*input, *tree, env_list);
	if (g_signum == SIGINT)
	{
		free_tree(*tree);
		*tree = NULL;
		g_signum = 0;
		env_list->last_exit_status = 130;
		return (1);
	}
	return (0);
}

static void handle_cmds(t_tree *tree, t_env_list *env_struct_lst)
{
	t_node	*cmd_node;

	cmd_node = go_first_cmd(tree);
	if (tree->num_pipes > 0)
		env_struct_lst->last_exit_status = exec_pipeline(env_struct_lst, tree);
	else if (cmd_node)
		env_struct_lst->last_exit_status = handle_single_command(env_struct_lst, tree, cmd_node);
}

static void handle_readline(t_env_list *env_struct_lst)
{
	char 	*input;
	t_tree	*tree;
	
	tree = NULL;
	while (1)
	{
		input = readline("\001\033[1;34m\002minihell$\001\033[0m\002 ");
		g_signum = 0;
		handle_input(input, env_struct_lst);
		if (handle_parsing(&tree, &input, env_struct_lst) != 0)
		{
			free(input);
			input = NULL;
			continue;
		}
		// print_cmd_nodes_readable(tree);
		handle_cmds(tree, env_struct_lst);
		free_tree(tree);
		free(input);
		tree = NULL;
		input = NULL;
	}
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out
/**
 * valgrind -q --track-fds=yes --trace-children=yes --log-fd=9 9>&2 2>/dev/null ./minishell
 valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./minishell

 valgrind -q --track-fds=yes --leak-check=full ./minishell

 */

// int main(int argc, char **argv, char **envp) {
// 	(void) argc;
// 	(void) argv;

// 	if (setup_sigint_prompt() == -1)
// 	{
// 		return (EXIT_FAILURE);
// 	}
// 	if (setup_sigquit_prompt() == -1)
// 	{
// 		return (EXIT_FAILURE);
// 	}
// 	t_env_list *env_struct_lst = copy_env(envp); 
// 	if (!env_struct_lst) {
//         write(2, "Failed to initialize environment\n", 33);
// 		//termios_sigquit_on();
//         return (EXIT_FAILURE);
//     }
// 	handle_readline(env_struct_lst);
// 	clear_history();
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	t_env_list	*env_struct_lst;
	t_tree		*tree;
	t_data		data;

	(void)argc;
	(void)argv;
	tree = NULL;
	if (setup_sigint_prompt() == -1 || setup_sigquit_prompt() == -1)
	return (EXIT_FAILURE);
	env_struct_lst = copy_env(envp);
	if (!env_struct_lst)
		return (write(2, "Failed to initialize environment\n", 33),
		EXIT_FAILURE);
	handle_readline(env_struct_lst);
	if (g_signum == SIGINT)
	{
		total_liberation(tree, env_struct_lst, &data, data.pipes);
		write(1, "\n", 1);
		clear_history();
		exit(130);
	}
	return (clear_history(), 0);
}
