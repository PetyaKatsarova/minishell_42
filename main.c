/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/21 15:23:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/04/25 18:38:11 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int handle_readline(t_env_list *env_struct_lst)
{
	char 	*input;
	t_token	*token_list = NULL;
	t_tree	*tree;
	t_node	*cmd_node;
	int		exit_status = 0;
	
	while (1)
	{
		input = readline("\033[1;34mminihell$\033[0m ");
		if (!input)
		{
			write(STDERR_FILENO, "exit\n", 5);
			clear_history();
			free_t_env(env_struct_lst);
			return (EXIT_FAILURE);
		}
		if (*input)
			add_history(input);
		if (prelim_syn_check(input, &exit_status) != 0)
		{
			free(input);
			continue;
		}
		lexer(&token_list, input, env_struct_lst, exit_status);
		exit_status = syn_check(&token_list);
		if (exit_status != 0)
		{
			free_list(&token_list);
			free(input);
			continue;
		}
		tree = treenew(token_list, exit_status);
		parser(tree);
		//print_cmd_nodes(tree);
		cmd_node = go_first_cmd(tree);
		//print_token_type(cmd_node->token_type);
		//printf("argv=%s, argv[1]=%s\n", cmd_node->argv[0], cmd_node->argv[1]);
		if (get_num_pipes(tree) > 0)
			exit_status = exec_pipeline(env_struct_lst, tree);
		else if (cmd_node) // handles single commands
		{
			if (cmd_node->token_type == TOKEN_WORD)
				exit_status = exec_on_path(env_struct_lst, cmd_node, 0);
			else
				exit_status = execute_builtin(cmd_node, tree, env_struct_lst);
		}
		env_struct_lst->last_exit_status = exit_status;
		free_tree(tree);
		free(input);
	}
	return (exit_status);
}

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minishell
// valgrind -s --leak-check=full --track-origins=yes ./minishell

//valgrind --tool=memcheck --track-fds=yes --trace-children=yes ./minishell

//export b | export bb | echo | b | pwd | cat main.c | grep main.c


//valgrind --track-fds=yes --trace-children=yes --log-fd=2 ./minishell
/**
 * !! NB!!
 * This is also fine.

🔹 `in use at exit: 26,383 bytes in 24 blocks`  
 → This memory is **still reachable**, not leaked.  
 → It’s **held by `ls`**, likely for caching, internal buffers, or locale settings.

🔹 `total heap usage: 258 allocs, 234 frees`  
 → Normal behavior: many programs allocate memory and let the OS clean it up on exit.

No `definitely lost` memory → **no real leaks**.
**Conclusion:** everything’s working as expected.
1 std FD → stdout (you ran under Valgrind, which redirects others).

3 inherited FDs:

fd 103: /usr/share/code/v8_context_snapshot.bin (VSCode-related).

fd 38: /dev/ptmx (pseudo-terminal for VSCode terminal).

fd 37: VSCode terminal log (ptyhost.log).
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
	free_t_env(env_struct_lst); //this is done in exit.c: in case i have invalid exec path: testing
	// free_tree(tree); ??
	clear_history();
	return (0);
}
/**
 * Command	What Happens	$?
bla	command not found	127
exit	Exits with code 127	—
echo $?	Doesn't run — shell has exited 
 */