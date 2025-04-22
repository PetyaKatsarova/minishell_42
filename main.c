/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/21 15:23:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/21 20:45:04 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	lex_and_parse(char *input, t_tree **tree)
{
	t_token	*token_list;
	
	if (prelim_syn_check(input) < 0)
	{
		// TODO: UPDATE LAST_EXIT_STATUS in env_struct_lst
		free(input);
		return (-1);
	}
	token_list = NULL;
	lexer(&token_list, input);
	*tree = treenew(token_list);
	if (parser(*tree) < 0)
	{
		free_tree(*tree);
		free(input);
		return (-1);
	}
	return (0);
}

static int handle_readline(t_env_list *env_struct_lst)
{
	while (1)
	{
		char	*input;
		//t_token	*token_list;
		t_tree	*tree;
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

		if (lex_and_parse(input, &tree) < 0)
		{
			continue;
		}
		cmd_node = go_first_cmd(tree);		
		while (cmd_node != NULL)
		{
			env_struct_lst->last_exit_status = handle_commands( env_struct_lst, tree, cmd_node);
			cmd_node = go_next_cmd(cmd_node);
			
		}
		free_tree(tree);
		free(input);
	}
	return (0);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minishell
// valgrind -s --leak-check=full --track-origins=yes ./minishell

// dont work: cat
// 

int main(int argc, char **argv, char **envp) {
	(void) argc;
	(void) argv;

	t_env_list *env_struct_lst = copy_env(envp); 
	if (!env_struct_lst) {
        perror("Failed to initialize environment");
        return (EXIT_FAILURE);
    }
	handle_readline(env_struct_lst); // question by jan: handle_readline returns an int, but we are not using the int here. Should we change handle_readline to void?
	free_t_env(env_struct_lst); //this is done in exit.c: in case i have invalid exec path: testing
	clear_history();
	return (0);
}
