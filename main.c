/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/21 15:23:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/23 10:33:56 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


static int handle_readline(t_env_list *env_struct_lst)
{
	while (1)
	{
		char *input;
		t_token	*token_list = NULL;
		t_tree	*tree;
		t_node	*cmd_node;
		int		exit_status;

		input = readline("\033[1;34mminihell$\033[0m ");
		exit_status = -1;
		if (!input)
		{
			write(STDERR_FILENO, "exit\n", 5);
			clear_history();
			free_t_env(env_struct_lst);
			return (EXIT_FAILURE);
		}
		if (*input)
			add_history(input);
		if (prelim_syn_check(input) < 0)
		{
			free(input);
			continue;
		}
		lexer(&token_list, input);
		tree = treenew(token_list);
		parser(tree);
		cmd_node = go_first_cmd(tree);
		if (get_num_pipes(tree) > 0)
			exec_pipeline(env_struct_lst, tree);
		else if (cmd_node) // handles single commands
		{
			exit_status = execute_builtin(cmd_node, tree, env_struct_lst);
			// todo: how to implement update of shlvl?
			if (exit_status == -1)
				exec_on_path(env_struct_lst, cmd_node, 0);
		}
		free_tree(tree);
		free(input);
	}
	return (0);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minishell
// valgrind -s --leak-check=full --track-origins=yes ./minishell
// valgrind --leak-check=full --show-leak-kinds=all ./your_program


int main(int argc, char **argv, char **envp) {
	(void) argc;
	(void) argv;

	t_env_list *env_struct_lst = copy_env(envp); 
	if (!env_struct_lst) {
        perror("Failed to initialize environment");
        return (EXIT_FAILURE);
    }
	handle_readline(env_struct_lst);
	free_t_env(env_struct_lst); //this is done in exit.c: in case i have invalid exec path: testing
	// free_tree(tree); ??
	clear_history();
	return (0);
}
