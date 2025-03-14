# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pekatsar <pekatsar@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/11/10 13:25:44 by pekatsar      #+#    #+#                  #
#    Updated: 2024/11/10 13:25:46 by pekatsar      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =	 libftprintf.a
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIB = ar rcs

SOURCES = ft_printf.c \
		ft_print_utils.c \
		ft_print_num.c \
		ft_print_unsigned_int.c \
		ft_print_hex.c \
		ft_print_ptr.c \
		
OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(LIBFT_PATH)

all:	$(LIBFT) $(NAME)

$(LIBFT):
		make -C $(LIBFT_PATH)

$(NAME):	$(OBJECTS)
			cp $(LIBFT) $(NAME)
			$(LIB) $(NAME) $(OBJECTS)

clean:
		make clean -C $(LIBFT_PATH)
		$(RM) $(OBJECTS)

fclean:	clean
		make fclean -C $(LIBFT_PATH)
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re libft

test: all
	$(CC) $(CFLAGS) main.c -L. -lftprintf && ./a.out
#	$(CC)  -g -fsanitize=address main.c $(NAME) && ./a.out
# add $(CFLAGS) after CC