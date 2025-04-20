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
			//free_tree(tree); todo .....
			// DO I NEED TO FREE token list and comdnode?
			return (EXIT_FAILURE); // NEED TO CLEAR ALL MALLOCS 
		}
		if (*input) // DO I NEED * and why
			add_history(input);
		token_list = NULL;
		//printf("\ninput: %s\n", input);
		if (prelim_syn_check(input) < 0)
		{
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
			// printf("last exit status: %d\n", env_struct_lst->last_exit_status);
			cmd_node = go_next_cmd(cmd_node);
		}
		// print_cmd_nodes(tree);
		free_tree(tree);
		free(input);
	}
	return (0);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minishell

// valgrind -s --leak-check=full --track-origins=yes ./minishell
// ls -l | wc -l
// ls -l | grep main
// bla | ls -l | grep main
// -rwxrwxrwx 1 petya petya   2448 Apr 20 18:27 main.c
// -rwxrwxrwx 1 petya petya  12856 Apr 20 18:26 main.o
// Command 'bla' not found, did you mean:

// pwd | ls -l | cd
// exit | echo bla | pwd
// pwd | pwd | pwd
// echo bla | pwd | exit
// bash | bash | bash : shlvl 1? i am in wsl, check on linux
// exit | echo bla | pwd
// echo bla | pwd | wc -w
// 3

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
