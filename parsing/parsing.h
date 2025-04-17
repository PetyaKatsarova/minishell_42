
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <assert.h> // remove for eval

typedef enum	e_state {
	OUTSIDE,
	INSIDE_SINGLES,
	INSIDE_DOUBLES
}	e_state;

typedef enum	e_token {
	TOKEN_NULL,

	TOKEN_PIPE,

	// redirects
	TOKEN_INPUT_REDIRECT,
	TOKEN_OUTPUT_REDIRECT,
	TOKEN_HEREDOC,
	TOKEN_APPEND_OUTPUT_REDIRECT,

	// inbuilts
	TOKEN_ECHO,
	TOKEN_CD,
	TOKEN_PWD,
	TOKEN_EXPORT,
	TOKEN_UNSET,
	TOKEN_ENV,
	TOKEN_EXIT,

	// words
	TOKEN_WORD
}	e_token;

// nodes for token list

typedef struct	s_token {
	char			*lexeme;
	e_token			token_type;			
	struct s_token	*next;
}	t_token;

// nodes for syntax tree:

typedef struct	s_tree {
	int				num_pipes;
	t_token			*token_list;
	struct s_node	*root;
}	t_tree;

typedef struct	s_node {
	struct s_node	*parent;
	e_token			token_type;
	char			**argv;
	struct s_node	*producer;
	struct s_node	*consumer;
	struct s_node	*redirects;
	char			*redir_path;
}	t_node;

// lexer functions
int			check_quotes(char *input);
void		lexer(t_token **head, char *input);
t_token		*consume_chars(t_token *tail, char **input);
t_token 	*consume_special_delim(t_token *tail, char **input);
t_token		*tokennew(t_token *tail, char *lexeme, e_token token_type);
bool		isendword(e_state state, char c);
int			getwordlen(char *input);
void		free_list(t_token **head);
bool		is_whitespace(char c);
int			set_state(e_state state, char c);
bool		is_special_delim(char c);

// parser functions
t_node		*nodenew(e_token token_type, t_node *parent);
t_tree		*treenew(t_token *token_list);
void		parser(t_tree *tree);
t_node		*go_first_pipe(t_tree *tree);
t_node		*go_next_pipe(t_node *current);
void		consume_token_list(t_tree *tree);
t_node		*go_first_cmd(t_tree *tree);
t_node		*go_next_cmd(t_node *current);
int			get_num_pipes(t_tree *tree);
void		make_pipe_nodes(t_tree *tree);
void		make_cmd_nodes(t_tree *tree);

// test functions
void		printlist(t_token *token_list);
void		print_token_type(e_token token_type);
void		print_state(e_state state);
void		print_argv(t_node *node);
void		print_node(t_node *node);
void		print_cmd_nodes(t_tree *tree);

#endif