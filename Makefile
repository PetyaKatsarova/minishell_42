# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: petya <petya@student.42.fr>                  +#+                      #
#                                                    +#+                       #
#    Created: 2025/02/04 11:27:44 by pekatsar      #+#    #+#                  #
#    Updated: 2025/03/14 17:10:42 by pekatsar      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME     := minishell
CC       := cc
CFLAGS   := -Wall -Wextra -Werror -g
LIBFT    := LIBFT

HEADERS  := -I ./include -I $(LIBFT)
LIBS     := -L$(LIBFT) -lft -lreadline

SRCS     := main.c
OBJS     := $(SRCS:.c=.o)

all: libft $(NAME)

libft:
	@make -C $(LIBFT)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && echo "Build successful!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re libft
