# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: petya <petya@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 11:27:44 by pekatsar          #+#    #+#              #
#    Updated: 2025/03/25 16:30:33 by petya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     := minishell
CC       := cc
CFLAGS   := -Wall -Wextra -Werror -g
LIBFT    := libs/libft

HEADERS  := -I ./include -I $(LIBFT)/include
LIBS     := -L$(LIBFT) -lft -lreadline  # Use -lft instead of -lftprintf

SRCS     := execution/built_ins/pwd.c \
			execution/built_ins/cd.c \
			execution/built_ins/echo.c \
			execution/built_ins/env.c \
			execution/utils.c \
			execution/init_env.c \
			main.c
OBJS     := $(SRCS:.c=.o)

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
