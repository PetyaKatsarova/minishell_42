/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parsing.h                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/06 17:55:54 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/05/06 17:55:56 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

/* forward declarations of structs from minishell.h */
typedef struct s_env		t_env;
typedef struct s_env_list	t_env_list;

typedef enum e_state
{
	OUTSIDE,
	INSIDE_SINGLES,
	INSIDE_DOUBLES
}	t_state;

typedef enum e_type
{
	TOKEN_NULL,
	PIPE,
	INPUT_REDIR,
	OUTPUT_REDIR,
	HEREDOC,
	APP_OUT_REDIR,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	WORD
}	t_type;

/* nodes for token list */
typedef struct s_token
{
	char			*lexeme;
	t_type			token_type;			
	struct s_token	*next;
}	t_token;

/* nodes for syntax tree */
typedef struct s_tree
{
	int				num_pipes;
	t_token			*token_list;
	struct s_node	*root;
}	t_tree;

typedef struct s_node
{
	struct s_node	*parent;
	t_type			token_type;
	char			**argv;
	struct s_node	*producer;
	struct s_node	*consumer;
	struct s_node	*redirects;
	char			*redir_path;
	char			*heredoc_str;
}	t_node;

/* data container for lexeme parsing */
typedef struct s_parsing_data
{
	char		*new;
	int			exit_status;
	char		*input;
	size_t		size;
	t_env_list	*env_list;
	t_tree		*tree;
}	t_parsing_data;

/* lexer functions */
int		pre_tokenization_syn_check(char *input, t_env_list *env_list);
void	lexer(t_token **head, char *input, t_env_list *env_list);
t_token	*consume_chars(t_token *tail, char **cpy);
t_token	*consume_special_delim(t_token *tail, char **cpy);
t_token	*tokennew(t_token *tail, char *lexeme, t_type token_type);
bool	isendword(t_state state, char c);
int		getwordlen(char *input);
void	free_list(t_token **head);
bool	is_whitespace(char c);
int		set_state(t_state state, char c);
bool	is_special_delim(char c);
int		post_tokenization_syn_check(t_token *current, t_env_list *env_list);
void	exit_failure_lexer(t_token **head, char *input, t_env_list *env_list);

/* parser functions */
t_node	*nodenew(t_type token_type, t_node *parent, t_parsing_data *data);
t_tree	*treenew(t_token *token_list, t_env_list *env_list, char *input);
void	parser(char *input, t_tree *tree, t_env_list *env_list);
t_node	*go_first_pipe(t_tree *tree);
t_node	*go_next_pipe(t_node *current);
void	consume_token_list(t_parsing_data *data);
t_node	*go_first_cmd(t_tree *tree);
t_node	*go_next_cmd(t_node *current);
t_node	*go_next_redir(t_node *current);
int		get_num_pipes(t_tree *tree);
void	make_pipe_nodes(t_parsing_data *data);
void	make_cmd_nodes(t_parsing_data *data);
void	free_tree(t_tree *tree);
bool	is_redir(t_type token_type);
char	*parse_lexeme(char *lexeme, t_parsing_data *data);
void	exit_failure_parser(t_parsing_data *data);
int		get_type(char *str);
char	**make_argv(t_token *token, t_parsing_data *data);
bool	is_valid_var_char(char c);
void	copy_char(char **target, char **source, t_parsing_data *data);
char	*allocate_str(t_parsing_data *data);
char	*reallocate_str(char *str, t_parsing_data *data);
int		my_strcmp(char *s1, char *s2);
void	expand(char **cpy, char **lexeme, t_parsing_data *data);
void	expand_variable(char **cpy, char **lexeme, t_parsing_data *data);
void	expand_exit_status(char **cpy, char **lexeme, t_parsing_data *data);
char	*parse_heredoc(char *lexeme, t_parsing_data *data);
void	cleanup_heredoc_loop(int *cpy_stdin, t_parsing_data *data, char **input);
void	setup_heredoc_loop(int *cpy_stdin, t_parsing_data *data, char **cpy_new);

/* test functions */
void	printlist(t_token *token_list);
void	print_token_type(t_type token_type);
void	print_state(t_state state);
void	print_argv(t_node *node);
void	print_node(t_node *node);
void	print_cmd_nodes(t_tree *tree);
void	print_redir_node(t_node *node);
void	print_cmd_nodes_readable(t_tree *tree);
void	print_cmd_node_readable(t_node *node);

#endif
