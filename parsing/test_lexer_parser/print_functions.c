/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_functions.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/01 12:19:41 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/01 12:19:44 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static const char	*g_token_strings[] = {"TOKEN_NULL",
	"TOKEN_PIPE",
	"TOKEN_INPUT_REDIRECT",
	"TOKEN_OUTPUT_REDIRECT",
	"TOKEN_HEREDOC",
	"TOKEN_APPEND_OUTPUT_REDIRECT",
	"TOKEN_ECHO",
	"TOKEN_CD",
	"TOKEN_PWD",
	"TOKEN_EXPORT",
	"TOKEN_UNSET",
	"TOKEN_ENV",
	"TOKEN_EXIT",
	"TOKEN_WORD"};

static const char	*g_state_strings[] = {"OUTSIDE",
	"INSIDE_SINGLES",
	"INSIDE_DOUBLES"};

void	printlist(t_token *token_list)
{
	t_token	*curr;

	curr = token_list;
	printf("\nOUTPUT LEXER: LINKED LIST:\n");
	while (curr)
	{
		printf("\n  %s: %s\n", g_token_strings[curr->token_type], curr->lexeme);
		curr = curr->next;
	}
	printf("\n");
}

void	print_token_type(e_token token_type)
{
	printf("%s\n", g_token_strings[token_type]);
}

void	print_state(e_state state)
{
	printf("state: %s\n", g_state_strings[state]);
}

void	print_argv(t_node *node)
{
	int		i;
	bool	first;

	i = 0;
	first = true;
	printf("argv: ");
	if (node->argv == NULL)
	{
		printf("%p", node->argv);
	}
	while (node->argv != NULL && *(node->argv + i) != NULL)
	{
		if (!first)
			printf(", ");
		printf("%s", *(node->argv + i));
		first = false;
		i++;
	}
	printf("\n");
}
