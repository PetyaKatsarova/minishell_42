NAME = parsing

CC = cc
CFLAGS = -lreadline -g #-Wall -Wextra -Werror

GREEN		= \\033[0;32m
RED			= \\033[0;31m
RESET		= \\033[0m

SRCS = 	lexer/lexer.c \
		lexer/prelim_syn_check.c \
		lexer/consume_input.c \
		lexer/utils.c \
		lexer/list_utils.c \
		parser/tree_utils.c \
		parser/tree_navigation.c \
		parser/tree_interface.c \
		parser/parser.c \
		parser/consume_token_list.c \
		parser/free_tree.c \
		parser/syn_check.c \
		parser/parser_utils.c \
		test_lexer_parser/test.c \
		test_lexer_parser/print_functions.c

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo -e "$(GREEN)\n*** parsing compiled successfully ***\n$(RESET)"

clean:
	rm -f $(OBJS)
	@echo -e "$(RED)\n*** object files cleaned ***\n$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo -e "$(RED)\n*** executables cleaned ***\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re