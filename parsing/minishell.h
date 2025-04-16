
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum	e_state {
	OUTSIDE,
	INSIDE_SINGLES,
	INSIDE_DOUBLES
}	e_state;

typedef enum	e_token {
	TOKEN_PIPE,
	TOKEN_VAR,
	TOKEN_EXIT_STATUS,

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

	// words, strings
	TOKEN_WORD,
	TOKEN_SQ_STR,
	TOKEN_DQ_STR
}	e_token;

typedef struct	s_token {
	char			*lexeme;
	enum e_token	token_type;			
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
	enum e_token	token_type;
	char			*lexeme;
	struct s_node	*producer;
	struct s_node	*consumer;
	struct s_node	*flags;
	struct s_node	*parameters;
	struct s_node	*redirects;
	char			*redir_path;
}	t_node;

// typedef struct	s_pipe {
// 	enum e_token		TOKEN_PIPE;
// 	struct s_command	*producer;
// 	struct s_command	*consumer;
// 	struct s_pipe		*producer_pipe;
// 	struct s_pipe		*consumer_pipe;
// }	t_pipe;

// typedef struct	s_command {
// 	enum e_token		token_type;
// 	char				*lexeme;
// 	struct s_flags		*flags;
// 	struct s_parameters	*parameters;
// 	struct s_redirects	*redirects;
// }	t_command;

// typedef struct	s_flag {
// 	enum e_token	token_type;
// 	char			*lexeme;
// 	struct s_flag	*next;
// }	t_flag;

// typedef struct	s_parameter {
// 	enum e_token		token_type;
// 	char				*lexeme;
// 	struct s_parameter	*next;
// }	t_parameter;

// typedef struct	s_redirect {
// 	enum e_token		token_type;
// 	char				*path;
// 	struct s_redirect	*next;
// }	t_redirect;

// lexer functions
int			check_quotes(char *input);
t_token		*dq_str(t_token *tail, char **input);
void		lexer(t_token **head, char *input);
t_token		*consume_chars(t_token *tail, char **input);
t_token 	*consume_special_delim(t_token *tail, char **input);
t_token		*sq_str(t_token *tail, char **input);
t_token		*tokennew(t_token *tail, char *lexeme, enum e_token token_type);
int			getlen(char *input, char end);
bool		isendword(e_state state, char c);
int			getwordlen(char *input);
void		free_list(t_token **head);
bool		is_whitespace(char c);
int			set_state(e_state state, char c);
bool		is_special_delim(char c);

// parser functions
t_node		*nodenew(enum e_token token_type, char *lexeme, t_node *parent);
t_tree		*treenew(t_token *token_list);
void		parser(t_tree *tree, t_token *token_list);
t_node		*go_first_pipe(t_tree *tree);
t_node		*go_next_pipe(t_node *current);
void		consume_token_list(t_tree *tree);
t_node		*go_first_cmd(t_tree *tree);
t_node		*go_next_cmd(t_node *current);
int			get_num_pipes(t_tree *tree);


// test functions
void		printlist(t_token *token_list);
void		print_token_type(enum e_token token_type);
void		print_state(e_state state);

#endif