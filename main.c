/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/21 15:23:34 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/02 11:22:52 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

static int	handle_parsing(t_tree **tree, char **input, t_env_list *env_list)
{
	t_token	*token_list;
	
	token_list = NULL;
	if (pre_tokenization_syn_check(*input, env_list) != 0)
	{
		free(*input);
		*input = NULL;
		return (2);
	}
	lexer(&token_list, *input);
	if (post_tokenization_syn_check(token_list, env_list) != 0)
	{
		free_list(&token_list);
		free(*input);
		*input = NULL;
		return (2);
	}
	*tree = treenew(token_list, env_list, *input);
	parser(*input, *tree, env_list);
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
		input = readline("\033[1;34mminihell$\033[0m ");
		handle_input(input, env_struct_lst);
		if (handle_parsing(&tree, &input, env_struct_lst) != 0)
		{
			continue;
		}
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
