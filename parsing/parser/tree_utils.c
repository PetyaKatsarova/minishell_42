#include "../minishell.h"

t_node	*nodenew(enum e_token token_type, char *lexeme, t_node *parent)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
	{
		return (NULL); // add error handling: free all
	}
	new_node->parent = parent;
	new_node->token_type = token_type;
	new_node->lexeme = lexeme;
	new_node->producer = NULL;
	new_node->consumer = NULL;
	new_node->flags = NULL;
	new_node->parameters = NULL;
	new_node->redirects = NULL;
	new_node->redir_path = NULL;
	return (new_node);
}

t_tree	*treenew(t_token *token_list)
{
	t_tree	*new_tree;

	new_tree = malloc(sizeof(t_tree));
	if (new_tree == NULL)
	{
		return (NULL); // add error handling: free all
	}
	new_tree->num_pipes = 0;
	new_tree->token_list = token_list;
	new_tree->root = NULL;
	return (new_tree);
}

// t_pipe *pipenew(void)
// {
// 	t_pipe	*new_pipe;

// 	new_pipe = malloc(sizeof(t_pipe));
// 	if (new_pipe == NULL)
// 	{
// 		return (NULL); // add error handling
// 	}
// 	new_pipe->producer = NULL;
// 	new_pipe->consumer = NULL;
// 	new_pipe->producer_pipe = NULL;
// 	new_pipe->consumer_pipe = NULL;
// 	return (new_pipe);
// }

// t_command *commandnew(char *lexeme, enum e_token token_type)
// {
// 	t_command *new_command;

// 	new_command = malloc(sizeof(t_command));
// 	if (new_command == NULL)
// 	{
// 		return (NULL); // add error handling: free all
// 	}
// 	new_command->token_type = token_type;
// 	new_command->lexeme = lexeme;
// 	new_command->flags = NULL;
// 	new_command->parameters = NULL;
// 	new_command->redirects = NULL;
// 	return (new_command);
// }

// t_flag *flagnew(char *lexeme, enum e_token token_type)
// {
// 	t_flag	*new_flag;

// 	new_flag = malloc(sizeof(t_flag));
// 	if (new_flag == NULL)
// 	{
// 		return (NULL); // add error handling: free all
// 	}
// 	new_flag->token_type = token_type;
// 	new_flag->lexeme = lexeme;
// 	new_flag->next = NULL;
// 	return (new_flag);
// }

// t_parameter	*parameternew(char *lexeme, enum e_token token_type)
// {
// 	t_parameter	*new_parameter;

// 	new_parameter = malloc(sizeof(t_parameter));
// 	if (new_parameter == NULL)
// 	{
// 		return (NULL); // add error handling: free all
// 	}
// 	new_parameter->token_type = token_type;
// 	new_parameter->lexeme = lexeme;
// 	new_parameter->next = NULL;
// 	return (new_parameter);
// }

// t_redirect *redirectnew(enum e_token token_type)
// {
// 	t_redirect	*new_redirect;

// 	new_redirect = malloc(sizeof(t_redirect));
// 	if (new_redirect == NULL)
// 	{
// 		return (NULL); // add error handling: free all
// 	}
// 	new_redirect->token_type = token_type;
// 	new_redirect->next = NULL;
// 	return (new_redirect);
// }
