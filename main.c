/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/21 15:23:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/01 17:09:16 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * 		// printlist(token_list);
		//print_cmd_nodes(tree);
		//print_cmd_nodes_readable(tree);
 */

static void handle_input(char *input, t_env_list *env_struct_lst)
{
	if (!input)
	{
		write(STDERR_FILENO, "exit\n", 5);
		clear_history();
		free_t_env(env_struct_lst);
		//return (EXIT_FAILURE); todo: 
	}
	if (*input)
		add_history(input);
}

static void handle_cmds(t_tree *tree, t_env_list *env_struct_lst, t_node *cmd_node, int exit_status)
{
	int pipes;

	pipes = get_num_pipes(tree);
	if (pipes > 0) // todo apply redirections to all pipes
			exit_status = exec_pipeline(env_struct_lst, tree);
		else if (cmd_node) // handles single commands
			exit_status = handle_single_command(env_struct_lst, tree, cmd_node);
		env_struct_lst->last_exit_status = exit_status;
}

static int handle_readline(t_env_list *env_struct_lst)
{
	char 	*input;
	t_token	*token_list;
	t_tree	*tree;
	t_node	*cmd_node;
	int		exit_status = 0;
	
	token_list = NULL;
	while (1)
	{
		input = readline("\033[1;34mminihell$\033[0m ");
		handle_input(input, env_struct_lst);
		lexer(&token_list, input);
		if (syn_check(token_list) != 0)
		{
			exit_status = 2;
			free_list(&token_list);
			free(input);
			continue;
		}
		tree = treenew(token_list, env_struct_lst, input);
		parser(input, exit_status, tree, env_struct_lst);
		cmd_node = go_first_cmd(tree);
		handle_cmds(tree, env_struct_lst, cmd_node, exit_status);
		free_tree(tree);
		free(input);
	}
	return (exit_status);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out
/** valgrind --tool=memcheck --track-fds=yes --trace-children=yes ./minishell
 * 
 * valgrind --track-fds=yes --trace-children=yes ./minishell

 valgrind --leak-check=full --show-leak-kinds=all ./minishell

 valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./minishell
 */

 /**
  * !!NB!!
  * Ensure your user has this line in their ~/.inputrc:
set enable-bracketed-paste on
Or programmatically set it up in C:
rl_variable_bind("enable-bracketed-paste", "on");
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
	// free_t_env(env_struct_lst);
	env_struct_lst = NULL;
	clear_history();
	return (0);
}
