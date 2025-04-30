# **************************************************************************** #
#																			  #
#														 ::::::::			 #
#	Makefile										   :+:	:+:			 #
#													  +:+					 #
#	By: marvin <marvin@student.42.fr>				+#+					  #
#													+#+					   #
#	Created: 2025/02/04 11:27:44 by pekatsar	  #+#	#+#				  #
#	Updated: 2025/04/09 16:42:43 by anonymous	 ########   odam.nl		  #
#																			  #
# **************************************************************************** #

NAME	 := minishell
CC	   := cc
CFLAGS   := -g -Wall -Wextra -Werror -g #-fsanitize=address
LIBFT	:= libs/libft

HEADERS  := -I ./include -I $(LIBFT)/include
LIBS	 := -L$(LIBFT) -lft -lreadline  # Use -lft instead of -lftprintf

SRCS	 := execution/built_ins/pwd.c \
			execution/built_ins/cd.c \
			execution/built_ins/echo.c \
			execution/built_ins/env.c \
			execution/built_ins/exit.c \
			execution/built_ins/unset.c \
			execution/built_ins/export_utils.c \
			execution/built_ins/export.c \
			execution/freeing.c \
			execution/init_env.c \
			execution/utils.c \
			execution/exec_pipes.c \
			execution/handle_commands.c \
			execution/redirects.c \
			execution/executables/exec_on_path.c \
			execution/executables/parse_path.c \
			execution/executables/helpers.c \
			execution/executables/manage_files.c \
			main.c \
			parsing/lexer/lexer_main.c \
			parsing/lexer/prelim_syn_check.c \
			parsing/lexer/consume_input.c \
			parsing/lexer/utils.c \
			parsing/lexer/list_utils.c \
			parsing/lexer/syn_check.c \
			parsing/parser/tree/tree_utils.c \
			parsing/parser/tree/tree_navigation.c \
			parsing/parser/tree/tree_interface.c \
			parsing/parser/parser_main.c \
			parsing/parser/parse_token_list.c \
			parsing/test_lexer_parser/print_functions.c \
			parsing/parser/tree/tree_free.c \
			parsing/parser/utils/parser_utils_1.c \
			parsing/parser/utils/parser_utils_2.c \
			parsing/parser/utils/parser_utils_3.c \
			parsing/parser/parse_lexeme.c \

OBJS	 := $(SRCS:.c=.o)

# Default target to build everything
all: libft $(NAME)

# Build the libft library
libft:
	@make -C $(LIBFT)

# Link the object files and create the executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && echo "Build successful!"

# Compile source files to object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

valgrind_cd: $(NAME)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) cd

# Clean up object files
clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT) clean

# Clean up and remove the executable
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean

# Rebuild everything (clean + all)
re: fclean all

.PHONY: all clean fclean re libft
