/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   main.c											 :+:	:+:			*/
/*													 +:+					*/
/*   By: marvin <marvin@student.42.fr>				+#+					 */
/*												   +#+					  */
/*   Created: 2025/03/14 11:17:10 by pekatsar	  #+#	#+#				 */
/*   Updated: 2025/04/10 13:36:26 by pekatsar	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "includes/minishell.h"

static int handle_readline(t_env_list *env_struct_lst)
{
	while (1)
	{
		char	*input;
		t_token	*token_list;
		t_tree	*tree;
		(void) env_struct_lst;
		t_node	*cmd_node;
	
		input = readline("\033[1;34mminihell$\033[0m ");
		if (!input) // TODO ??? 
		{
			printf("exit with no input collected.\n");
			clear_history(); // for mem leaks
			free_t_env(env_struct_lst);
			// DO I NEED TO FREE TREE? YES.. TODO
			return (EXIT_FAILURE); // NEED TO CLEAR ALL MALLOCS 
		}
		if (*input) // DO I NEED * and why
			add_history(input);

		token_list = NULL;
		//printf("\ninput: %s\n", input);
		if (prelim_syn_check(input) < 0)
		{
			// TODO: UPDATE LAST_EXIT_STATUS in env_struct_lst
			free(input);
			continue;
		}
		lexer(&token_list, input);
		//printlist(token_list);
		tree = treenew(token_list);
		parser(tree);

		cmd_node = go_first_cmd(tree);		
		while (cmd_node != NULL)
		{
		//printf("cmd_node: %s\n", cmd_node->argv[0]);
			env_struct_lst->last_exit_status = handle_commands( env_struct_lst, tree, cmd_node);
			cmd_node = go_next_cmd(cmd_node);
			
		}

		//print_cmd_nodes(tree);
		free_tree(tree);
		free(input);
	}
	return (0);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minishell

// valgrind -s --leak-check=full --track-origins=yes ./minishell


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
	clear_history();
	return (0);
}
