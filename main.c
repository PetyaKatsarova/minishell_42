/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/21 15:23:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/02 10:53:39 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * 		// printlist(token_list);
		//print_cmd_nodes(tree);
		//print_cmd_nodes_readable(tree);
				// printlist(token_list);
		//print_cmd_nodes(tree);
		//print_cmd_nodes_readable(tree);
 */

 /**
  * user pressed ctr+d: no input
  */
static void handle_input(char *input, t_env_list *env_struct_lst)
{
	if (!input)
	{
		write(STDERR_FILENO, "exit\n", 5);
		clear_history();
		free_t_env(env_struct_lst);
		exit(EXIT_FAILURE);
	}
	if (*input)
		add_history(input);
}

static int	handle_parsing(t_tree **tree, char *input, int *exit_status, t_env_list *env_list)
{
	t_token	*token_list;
	
	token_list = NULL;
	if (prelim_syn_check(input, exit_status) != 0)
	{
		free(input);
		return (2);
	}
	lexer(&token_list, input);
	if (syn_check(token_list) != 0)
	{
		*exit_status = 2;
		free_list(&token_list);
		free(input);
		return (2);
	}
	*tree = treenew(token_list, env_list, input);
	parser(input, *exit_status, *tree, env_list);
	return (0);
}

static void handle_cmds(t_tree *tree, t_env_list *env_struct_lst, t_node *cmd_node, int exit_status)
{
	//int pipes;

	//pipes = get_num_pipes(tree);
	if (tree->num_pipes > 0)
			exit_status = exec_pipeline(env_struct_lst, tree);
	else if (cmd_node)
		exit_status = handle_single_command(env_struct_lst, tree, cmd_node);
	env_struct_lst->last_exit_status = exit_status;
}

static int handle_readline(t_env_list *env_struct_lst)
{
	char 	*input;
	t_tree	*tree;
	t_node	*cmd_node;
	int		exit_status = 0;
	
	tree = NULL;
	while (1)
	{
		input = readline("\033[1;34mminihell$\033[0m ");
		handle_input(input, env_struct_lst);
		if (handle_parsing(&tree, input, &exit_status, env_struct_lst) != 0)
			continue;
		cmd_node = go_first_cmd(tree);
		handle_cmds(tree, env_struct_lst, cmd_node, &exit_status);
		free_tree(tree);
		free(input);
		tree = NULL;
		input = NULL;
	}
	return (exit_status);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out
/**
 * valgrind -q --track-fds=yes --trace-children=yes --log-fd=9 9>&2 2>/dev/null ./minishell
 valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./minishell
 */

int main(int argc, char **argv, char **envp) {
	(void) argc;
	(void) argv;

	t_env_list *env_struct_lst = copy_env(envp); 
	if (!env_struct_lst) {
        perror("Failed to initialize environment");
        return (EXIT_FAILURE);
    }
	handle_readline(env_struct_lst);
	env_struct_lst = NULL;
	clear_history();
	return (0);
}

