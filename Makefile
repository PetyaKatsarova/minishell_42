# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: petya <petya@student.42.fr>                  +#+                      #
#                                                    +#+                       #
#    Created: 2025/02/04 11:27:44 by pekatsar      #+#    #+#                  #
#    Updated: 2025/03/14 17:39:30 by pekatsar      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME     := minishell
CC       := cc
CFLAGS   := -Wall -Wextra -Werror -g
FT_PRINTF := libs/ft_printf

HEADERS  := -I ./include -I $(FT_PRINTF)/include
LIBS     := -L$(FT_PRINTF) -lftprintf -lreadline

SRCS     := main.c
OBJS     := $(SRCS:.c=.o)

all: ft_printf $(NAME)

ft_printf:
	@make -C $(FT_PRINTF)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && echo "Build successful!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(FT_PRINTF) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(FT_PRINTF) fclean

re: fclean all

.PHONY: all clean fclean re ft_printf
